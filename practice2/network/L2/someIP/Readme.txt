--> Pre 
     a. Automotive Ethernet (TCP/IP satck)
     b. Socket Programming
     c. Packet structures and protocols(IP,TCP,UDP,Ethernet)

--> OSI stack :A,P,S,T,N,D,P
              : connect any two computers to exchnge data

--> TCP/IP : use services over internet
           :Server offer services,client uses services,
           :A,T,N,Host to network layer(D+P)
           
           - APP layer:FTP,SOMEIP,AVB,Diagnostic over IP(DoIP)
           - Transport:TCP/UDP 
           - Network  :IP
           - D+P      : Ethernet,Automotive ethernet

--> singnal orented Archi vs service oriented Archi(SOA) 


--> SOME/IP: the Enabler of SOA in Automotive networks
           - (Scalable service-oriented Middleware over IP)designed to make ethernet data 
              transfer compatible with communication demands of Automotive ECUs.
           - SomeIP handles data-serialization,RPC(remote procedure call) and other essential tasks.
           -service req one ECU and Service provider another ecu works through sockets programming.

          --------        auto       -------
         | ECU 1  |-----------------| ECU 2 |
          --------    eth(TCP/IP)    -------
         publisher                  subscriber
            |                           |
    provides service            establish connection
            |                           |
  form of running program           process 2
        (process 1)                 (Reciver)
            |                           |
    process runs on a           runs on specific port no.
    specific port no.                   |   
(read/write data to process             |
       using ports)                     |
            |                           |
  combination of IP addr             (Socket)
  and port no.(socket) 
 

--> In SOA

 Publisher-offers(multiple) <-> Subscriber(wants to use any service)              
     \   \  \                                   / 
      \   \  service 1                 service 2(service discover)
       \   \    
        \   service 2
         \  
          service 3


 --> SOME/IP
     a. Basic Principle
     b. Service Discovery
     c. Service offerings
     d. Header format

--> Why SOME/IP?
    model the entire system as service interface(interportab/high bandwidth)
    send data to only receiver that needs it (all nodes dont have to hear)
    
--> Need for middleware(irrespective of  application):
      - to handle remote procedure calls,serialization
      - need to support Publish-subscribe model
      - Service Discovery
      - Segmentation of messages

NOTE: we can say middleware based on SOA is SOMEIP,scalable coz 
different platforms,service oriented coz Client-server,
over IP coz ethernet based.

           client |               | server
            app   |               | app
           -------------------------------
          |       SOMEIP Middleware       |
           -------------------------------
           TCP/IP |               |TCP/IP
            stack |<------------->| stack


--> flow of SOME/IP comm
______________________________     ______________________
                              |   |     
      ECU-A (server)          |   |   ECU-B(server)
      _________  ________     |   |     _________ 
     |service 1||service2|    |   |    |service  |
     |         ||        |    |   |    |         |
     |  method || method`|    |<->|    |  method |
     |    \/   ||  \/    |    |   |    |    \/   |
     |  field  || field  |    |   |    |  field  |
     |    ^    ||   ^    |    |   |    |    ^    |
     |  event  || event  |    |   |    |  event  |
      ---^-----  ---^----     |   |     -----^--- 
_________|__________|_________|   |__________|____________  
         |          |                        |
        ECU-C/D(client)                    ECU-E(client)

 1)ECU-A providing service: is a method,has a field and also has a event
 2)Service instances: ecu's can have multiple services 
 3)service interface: when we need to connect we use interface
 4)Event: is a messgae communicated from server to client when 
   something changed(value changed in field(status)so event 
   accured,changed becoz somebody ran a method/function).
   
   METHOD : setter(changes value),getter(reads value),
            request-response(call remotely,sends back data),
            fire-forget(send data no returning)
         

     Method call:-               Event:-
      ECU_A    ECU_B               client    server
        |        |                   |        |
with ret|*  req  |                   |*  subsc|
        |   *    |                   |   *    |
        |      * |                   |      * |
        |       *|                   |       *|
        |      * |                   |      * |
        |   *    |                   |   *    |
        |*  resp |                   |*  Ack  |

   :ecu1 every 2sec need temprature from ecu2 so register/subscribe 
    and every 2sec gets ,ecu3 dont need every 2sec but wants to 
    read at some point then request  and get value.   

--> SOME/IP Header
   
    MESSAGE ID(SERVICE ID/Method ID)[32bit]
    LENGTH[32bit]
    REQUEST ID(client/session ID)[32bit]
    PROTOCOL VER[8bit] | INTERFACE VER[8bit] | MESSG TYPE[8bit]|return code[8bit]
    PAYLOAD[variable size]

--> network flow:
    1)someip service discovery:services offered(multicast using 
      udp)from provider to subscriber,client which is interested 
      in the service it has to tell it and subscribe to event 
      group. (client side/subscribe message is unicast)
    2)work on data (exchange data):(req-response,)
    3)TCP/IP stack:any comm using TCP it needs -3 way hand shake,
      syn/synAck/AcksynAck      
-->
 

