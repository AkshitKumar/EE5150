/** Network topology:
*
*   P2P	            AP    		      STA
*    *		            *                 *
*    |   10.1.1.0      |      		      |
*   n0----------------n1     		      n2
*      point-to-point     Wifi 10.1.2.0
*
* ./waf --run scratch/thrptMcs
* 
*   Downlink traffic from Server to Client
* 	Tcp or UDP traffic be specified.
*   For different MCS value find the throughput 
* 
*   Standard Used: 802.11ac
*   Channel Model:  ConstantSpeedPropagationDelayModel 
* 					LogDistancePropagationLossModel
* 
* 	For graphs 2a) and  2b)
* 
* 		Plot the throughput graphs for vhtmcs values:  0,1,2,3,4,5,6,7,8
* 		Plot graphs for both UDP and TCP
* 
*   For graphs 2c)
* 
* 	For throughput vs distance graph Modify the code as follows:
* 
* Plot UDP throughput vs distance
* Set mcsvalue = 0;
* increase distance(d) of the client  in steps : 40,60,80,100,120,140,160,180
*      
*/


#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/internet-module.h"
#include "ns3/gnuplot.h"
#include <fstream>
#include <vector>
#include <cmath>

using namespace ns3;

int main (int argc, char *argv[])
{

	/** Initialization of necessary variables */
	
	double d = 20;               /// client  set at 20 meters from origin. 10 mtrs from AP
	
	double throughput = 0;       /// Initializing throughput variable
	
	double txpower = 16.0206;   ///default value
	
	bool udp = true; // tcp or udp
	
	std::fstream outFile;
	outFile.open ("thrptMcs.dat", std::fstream::in | std::fstream::out | std::fstream::app);
	
	std::cout<<"For mcsvalue"<<"\t"<<"Downlink Throughput (Mbps)"<<std::endl;
	
	/// Mcs value iterations
	/// This value is used to set the MCS value using wifiHelper
	
	for(int mcsvalue = 0 ; mcsvalue <= 8; mcsvalue++)
	{
		/// Creating one server, one accesspoint, one client.  
		NodeContainer server, accesspoint, station;
		server.Create (1);
		accesspoint.Create (1);
		station.Create (1);
		
		/// Adding server and accespoint into a single subnet.
		NodeContainer p2plink;
		p2plink = NodeContainer (server.Get (0), accesspoint.Get (0));
		
		/// Setting point to point channel parameters.
		PointToPointHelper p2phelp;
		
		p2phelp.SetDeviceAttribute ("DataRate", StringValue ("1Gbps"));
		p2phelp.SetChannelAttribute ("Delay", StringValue ("1us"));
		
		/// Installing point to point nodes on a device.
		NetDeviceContainer p2pdevice;
		p2pdevice = p2phelp.Install (p2plink);
		
		NetDeviceContainer wifistationdevice, wifiapdevice;
		
		
		///Setting up Wifi Channel and Channel properties
		YansWifiChannelHelper channel;
		channel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
		channel.AddPropagationLoss ("ns3::LogDistancePropagationLossModel","Exponent",DoubleValue(3));
		
		
		YansWifiPhyHelper phy =  YansWifiPhyHelper::Default ();
		phy.Set ("RxGain", DoubleValue (0) );
		phy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11_RADIO);
		
		 phy.Set("TxPowerStart",DoubleValue(txpower));
		 phy.Set("TxPowerEnd",DoubleValue(txpower));
		
		// create the channel object and associate to PHY layer object
		phy.SetChannel (channel.Create ());
		phy.Set ("ChannelNumber", UintegerValue (36) );
		phy.Set ("ChannelWidth", UintegerValue (20) );
		phy.Set ("ShortGuardEnabled", BooleanValue (true));
		
		WifiHelper wifi;
		// Set Wi-fi PHy properties
		wifi.SetStandard (WIFI_PHY_STANDARD_80211ac);
		
		//**********To set High Throughput wifi mac
		VhtWifiMacHelper mac = VhtWifiMacHelper::Default ();
		
				
		std::ostringstream oss;
		oss << "VhtMcs"<<mcsvalue;
		wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
		"DataMode",StringValue (oss.str()),
		"ControlMode",StringValue (oss.str()));
		
			
		/// Setting SSID.          
		Ssid ssid = Ssid ("simplewifi");
		
		/// Setting mac for client and installing on a device.
		mac.SetType ("ns3::StaWifiMac",
		"Ssid", SsidValue (ssid),
		"ActiveProbing", BooleanValue (false),
		"QosSupported", BooleanValue(true));
		
		wifistationdevice = wifi.Install (phy, mac, station);
		
		/// Setting mac for accesspoint and installing on a device.
		mac.SetType ("ns3::ApWifiMac",
		"Ssid", SsidValue (ssid),
		"BeaconGeneration", BooleanValue (true),
		"BeaconInterval",TimeValue (MicroSeconds (100000)),
		"QosSupported", BooleanValue(true));
		
		wifiapdevice = wifi.Install (phy, mac, accesspoint);
		
		/// Setting up mobility and positioning all nodes.
		MobilityHelper mobility;
		Ptr<ListPositionAllocator> positionAlloc1 = CreateObject<ListPositionAllocator> ();
		positionAlloc1->Add (Vector (0.0, 0.0, 0.0));    //server
		positionAlloc1->Add (Vector (10.0, 0.0, 0.0));  //access point
		positionAlloc1->Add (Vector (d, 0.0, 0.0));   //station
		mobility.SetPositionAllocator (positionAlloc1);
		
		mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
		/// Installing mobility on all nodes.
		mobility.Install (server);
		mobility.Install (accesspoint);
		mobility.Install (station);
		
		/// Setting up Internet stack
		InternetStackHelper stack;
		stack.Install (server);
		stack.Install (accesspoint);
		stack.Install (station);
		
		/// Addressing of IPv4
		Ipv4AddressHelper address;
		
		address.SetBase ("10.1.1.0", "255.255.255.0");
		Ipv4InterfaceContainer p2pinterface;
		p2pinterface = address.Assign (p2pdevice);
		
		address.SetBase ("10.1.2.0", "255.255.255.0");
		Ipv4InterfaceContainer apinterface, stainterface;
		apinterface = address.Assign (wifiapdevice);
		stainterface = address.Assign (wifistationdevice);
		
		/// Setting applications 
		ApplicationContainer sourceApps, sinkApps;
		
		if (udp)
		{
			uint16_t port = 50000;
			OnOffHelper onoff ("ns3::UdpSocketFactory",Address());
			onoff.SetAttribute ("OnTime",  StringValue ("ns3::ConstantRandomVariable[Constant=1]"));
			onoff.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));
			onoff.SetAttribute ("DataRate", StringValue ("100Mbps"));
			
			AddressValue remoteAddress (InetSocketAddress (stainterface.GetAddress (0), port));
			onoff.SetAttribute ("Remote", remoteAddress);
			sourceApps.Add (onoff.Install (server));
			
			Address LocalAddress (InetSocketAddress (Ipv4Address::GetAny (), port));
			PacketSinkHelper packetSinkHelper ("ns3::UdpSocketFactory", LocalAddress);
			sinkApps = packetSinkHelper.Install (station);
		}
		else // Tcp
		{
			uint16_t port = 9; 
			BulkSendHelper source ("ns3::TcpSocketFactory", Address ());
			source.SetAttribute ("MaxBytes", UintegerValue (0));
			
			AddressValue remoteAddress (InetSocketAddress (stainterface.GetAddress (0), port));
			source.SetAttribute ("Remote", remoteAddress);
			sourceApps = source.Install (server);
			
			PacketSinkHelper sink ("ns3::TcpSocketFactory",
			InetSocketAddress (Ipv4Address::GetAny (), port));
			
			sinkApps = sink.Install (station);
		}
		
		/// Setting the start time and stop time for source and sink applications.
		sourceApps.Start (Seconds (10.0));
		sourceApps.Stop (Seconds (20.0));
		
		sinkApps.Start (Seconds (10.0));
		sinkApps.Stop (Seconds (20.0));
		
		/// Setting a Routing Helper for packets to route through the nodes
		Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
		
		/// Setting Simulator Stop time to run and destroy for one
		/// time of simulation.
		Simulator::Stop (Seconds (20.0));
		Simulator::Run ();  
		Simulator::Destroy ();
		
		/// Calculating throughput using no.of bytes received at sink.     
		uint32_t totalbytesThrough = DynamicCast<PacketSink> (sinkApps.Get (0))->GetTotalRx ();
		throughput = totalbytesThrough * 8 / (10.0 * 1000000.0); //Mbit/s
		std::cout<<mcsvalue<<"\t\t"<< throughput << std::endl;
		
		//Adding this node and throughput value to file
		outFile << mcsvalue << "\t" << throughput << "\n";
		
		} // for different MCS value
		
	outFile.close ();
	return 0;
	
} // main
