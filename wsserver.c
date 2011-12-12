
#include "onvifH.h"
#include <pthread.h>


void *thread_handler(void *args)
{
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	struct Namespace namespaces[] =
	{   // {"ns-prefix", "ns-name"}
		{"SOAP-ENV", "http://www.w3.org/2003/05/soap-envelope"}, // MUST be first
		{"SOAP-ENC", "http://www.w3.org/2003/05/soap-encoding"}, // MUST be second
		{"xsi", "http://www.w3.org/2001/XMLSchema-instance"},    // MUST be third
		{"xsd", "http://www.w3.org/2001/XMLSchema"},
		{"wsa", "http://schemas.xmlsoap.org/ws/2004/08/addressing"},
        {"xmime", "http://tempuri.org/xmime.xsd" },
    	{"ns5", "http://www.w3.org/2004/08/xop/include" },
    	{"ns3", "http://www.onvif.org/ver10/schema" },
    	{"ns6", "http://docs.oasis-open.org/wsrf/bf-2" },
	    {"ns7", "http://docs.oasis-open.org/wsn/t-1" },
    	{"ns14", "http://www.w3.org/2005/08/addressing" },
    	{"ns11", "http://docs.oasis-open.org/wsrf/r-2" },
    	{"ns1", "http://www.onvif.org/ver10/deviceIO/wsdl" },
    	{"ns12", "http://www.onvif.org/ver20/imaging/wsdl" },
    	{"ns13", "http://www.onvif.org/ver20/ptz/wsdl" },
    	{"ns16", "http://www.onvif.org/ver10/events/wsdl/PullPointSubscriptionBinding" },
    	{"ns17", "http://www.onvif.org/ver10/events/wsdl/EventBinding" },
    	{"ns9", "http://www.onvif.org/ver10/events/wsdl" },
    	{"ns18", "http://www.onvif.org/ver10/events/wsdl/SubscriptionManagerBinding" },
      	{"ns19", "http://www.onvif.org/ver10/events/wsdl/NotificationProducerBinding" },
	    {"ns2", "http://www.onvif.org/ver10/media/wsdl" },
	    {"ns20", "http://www.onvif.org/ver10/events/wsdl/NotificationConsumerBinding" },
	    {"ns21", "http://www.onvif.org/ver10/events/wsdl/PullPointBinding" },
	    {"ns22", "http://www.onvif.org/ver10/events/wsdl/CreatePullPointBinding" },
	    {"ns23", "http://www.onvif.org/ver10/events/wsdl/PausableSubscriptionManagerBinding" },
	    {"ns4", "http://docs.oasis-open.org/wsn/b-2" },
	    {"ns8", "http://www.onvif.org/ver10/device/wsdl" },     
		{NULL, NULL} // end of table
	};
	//new thread
    pthread_t onvifthread;
    int temp;
    memset(&onvifthread, 0, sizeof(onvifthread));
    if((temp = pthread_create(&onvifthread, NULL, thread_handler, NULL)) != 0)
    {
        printf("htread create error!\n");
    }else{
        printf("thread create ok!\n");
    }
    
		int m, s ,i = 0;
    struct soap add_soap;
    soap_init(&add_soap);
    soap_set_namespaces(&add_soap, namespaces);
    m = soap_bind(&add_soap, NULL, 8800, 100);
    if (m < 0) 
	{
		soap_print_fault(&add_soap, stderr);
        exit(-1);
    }
    fprintf(stderr, "Socket connection successful:master socket = %d\n", m);

    while(1)
	{
        s = soap_accept(&add_soap);
        if (s < 0) 
		{
            soap_print_fault(&add_soap, stderr);
			fprintf(stderr, "Socket connection faild\n");
            exit(-1);
        }
        fprintf(stderr,"---------------------------------------socket = %d \n", s+(i++));
        soap_serve(&add_soap);
        soap_end(&add_soap);
    }
    if(onvifthread !=0) {
                pthread_join(onvifthread,NULL);
                printf("onvifthread is finished/n");
    }
    return 0;
}