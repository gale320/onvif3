#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Binding.nsmap"

#include <errno.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>

#define AUTO_URI_FLAG 1
#define RTSP_URI_XADDR "rtsp://192.168.1.248/stream1"

char *GetLocalHostIP()
{  
    char *ip=NULL;
    int fd;
    struct ifreq ifr; ///if.h
    struct sockaddr_in *addr = NULL;

    if ((fd = socket (AF_INET, SOCK_DGRAM, 0)) >= 0) //socket.h
    {
    	memset(&ifr, 0, sizeof(ifr));
    	
    	strncpy(ifr.ifr_name, "eth0", IFNAMSIZ - 1);
    	
    	if(ioctl(fd, SIOCGIFADDR, &ifr) == -1) {
    		perror("ioctl error");
    	}
    	
    	addr = (struct sockaddr_in *)&(ifr.ifr_addr);
    	ip = inet_ntoa(addr->sin_addr);
      
      close (fd);
    }
    
    return ip;
}

static int SetIPConf(const char *pszIP, const char *pszMask, const char *pszGateway)
{
	int fd = 0;
	
	fd = open("/etc/network/interfaces", O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP);
	if(fd < 0){
		perror("open file:");
		return -1;
	}
	
	char szBuf[1024] = {0};
	
	snprintf(szBuf, sizeof(szBuf), "# Configure Loopback\nauto lo\niface lo inet loopback\n\n\nauto eth0\niface eth0 inet static\naddress %s\nnetmask %s\ngateway %s\n",pszIP, pszMask, pszGateway);				
	int nBufLen = 0;
	int nRet = 0;
	
	nBufLen = strlen(szBuf);
	
	nRet = write(fd, szBuf, nBufLen);
	if (nBufLen != nRet) {
		perror("write ip interfaces failed:");
		return -2;
	}
	
	close(fd);
	return 0;
}


int __ns1__GetServiceCapabilities(struct soap* soap, struct _ns1__GetServiceCapabilities *ns1__GetServiceCapabilities, struct _ns1__GetServiceCapabilitiesResponse *ns1__GetServiceCapabilitiesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

int __ns1__GetAudioSources(struct soap* soap, struct _ns2__GetAudioSources *ns2__GetAudioSources, struct _ns2__GetAudioSourcesResponse *ns2__GetAudioSourcesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

int __ns1__GetAudioOutputs(struct soap* soap, struct _ns2__GetAudioOutputs *ns2__GetAudioOutputs, struct _ns2__GetAudioOutputsResponse *ns2__GetAudioOutputsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

int __ns1__GetVideoSources(struct soap* soap,struct _ns2__GetVideoSources *ns2__GetVideoSources,struct _ns2__GetVideoSourcesResponse *ns2__GetVideoSourcesResponse)
{
    printf("%s\n",__FUNCTION__);
    struct ns3__VideoResolution *pVideoResolution;
    pVideoResolution = (struct ns3__VideoResolution*)soap_malloc(soap,sizeof(struct ns3__VideoResolution));
    memset(pVideoResolution,0,sizeof(struct ns3__VideoResolution));
    pVideoResolution->Width = 1920;
    pVideoResolution->Height = 1080;

    ns2__GetVideoSourcesResponse->__sizeVideoSources = 1;
    ns2__GetVideoSourcesResponse->VideoSources = (struct ns3__VideoSource*)soap_malloc(soap,sizeof(struct ns3__VideoSource));
    memset(ns2__GetVideoSourcesResponse->VideoSources,0,sizeof(struct ns3__VideoSource));
    ns2__GetVideoSourcesResponse->VideoSources->Framerate = 30.000000;
    ns2__GetVideoSourcesResponse->VideoSources->Resolution = pVideoResolution;
    ns2__GetVideoSourcesResponse->VideoSources->token = "1";
    return SOAP_OK;
}

 int  __ns1__GetVideoOutputs(struct soap* soap, struct _ns1__GetVideoOutputs *ns1__GetVideoOutputs, struct _ns1__GetVideoOutputsResponse *ns1__GetVideoOutputsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns1__GetVideoSourceConfiguration(struct soap* soap, struct _ns1__GetVideoSourceConfiguration *ns1__GetVideoSourceConfiguration, struct _ns1__GetVideoSourceConfigurationResponse *ns1__GetVideoSourceConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns1__GetVideoOutputConfiguration(struct soap* soap, struct _ns1__GetVideoOutputConfiguration *ns1__GetVideoOutputConfiguration, struct _ns1__GetVideoOutputConfigurationResponse *ns1__GetVideoOutputConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns1__GetAudioSourceConfiguration(struct soap* soap, struct _ns1__GetAudioSourceConfiguration *ns1__GetAudioSourceConfiguration, struct _ns1__GetAudioSourceConfigurationResponse *ns1__GetAudioSourceConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns1__GetAudioOutputConfiguration(struct soap* soap, struct _ns1__GetAudioOutputConfiguration *ns1__GetAudioOutputConfiguration, struct _ns1__GetAudioOutputConfigurationResponse *ns1__GetAudioOutputConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns1__SetVideoSourceConfiguration(struct soap* soap, struct _ns1__SetVideoSourceConfiguration *ns1__SetVideoSourceConfiguration, struct _ns1__SetVideoSourceConfigurationResponse *ns1__SetVideoSourceConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns1__SetVideoOutputConfiguration(struct soap* soap, struct _ns1__SetVideoOutputConfiguration *ns1__SetVideoOutputConfiguration, struct _ns1__SetVideoOutputConfigurationResponse *ns1__SetVideoOutputConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns1__SetAudioSourceConfiguration(struct soap* soap, struct _ns1__SetAudioSourceConfiguration *ns1__SetAudioSourceConfiguration, struct _ns1__SetAudioSourceConfigurationResponse *ns1__SetAudioSourceConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns1__SetAudioOutputConfiguration(struct soap* soap, struct _ns1__SetAudioOutputConfiguration *ns1__SetAudioOutputConfiguration, struct _ns1__SetAudioOutputConfigurationResponse *ns1__SetAudioOutputConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns1__GetVideoSourceConfigurationOptions(struct soap* soap, struct _ns1__GetVideoSourceConfigurationOptions *ns1__GetVideoSourceConfigurationOptions, struct _ns1__GetVideoSourceConfigurationOptionsResponse *ns1__GetVideoSourceConfigurationOptionsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns1__GetVideoOutputConfigurationOptions(struct soap* soap, struct _ns1__GetVideoOutputConfigurationOptions *ns1__GetVideoOutputConfigurationOptions, struct _ns1__GetVideoOutputConfigurationOptionsResponse *ns1__GetVideoOutputConfigurationOptionsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns1__GetAudioSourceConfigurationOptions(struct soap* soap, struct _ns1__GetAudioSourceConfigurationOptions *ns1__GetAudioSourceConfigurationOptions, struct _ns1__GetAudioSourceConfigurationOptionsResponse *ns1__GetAudioSourceConfigurationOptionsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns1__GetAudioOutputConfigurationOptions(struct soap* soap, struct _ns1__GetAudioOutputConfigurationOptions *ns1__GetAudioOutputConfigurationOptions, struct _ns1__GetAudioOutputConfigurationOptionsResponse *ns1__GetAudioOutputConfigurationOptionsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns1__GetRelayOutputs(struct soap* soap, struct _ns8__GetRelayOutputs *ns8__GetRelayOutputs, struct _ns8__GetRelayOutputsResponse *ns8__GetRelayOutputsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns1__SetRelayOutputSettings(struct soap* soap, struct _ns1__SetRelayOutputSettings *ns1__SetRelayOutputSettings, struct _ns1__SetRelayOutputSettingsResponse *ns1__SetRelayOutputSettingsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns1__SetRelayOutputState(struct soap* soap, struct _ns8__SetRelayOutputState *ns8__SetRelayOutputState, struct _ns8__SetRelayOutputStateResponse *ns8__SetRelayOutputStateResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns12__GetServiceCapabilities(struct soap* soap, struct _ns12__GetServiceCapabilities *ns12__GetServiceCapabilities, struct _ns12__GetServiceCapabilitiesResponse *ns12__GetServiceCapabilitiesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

int __ns12__GetImagingSettings(struct soap* soap, struct _ns12__GetImagingSettings *ns12__GetImagingSettings, struct _ns12__GetImagingSettingsResponse *ns12__GetImagingSettingsResponse)
{
    printf("%s\n",__FUNCTION__);
    float a10086 = 0.0;
    
    struct ns3__BacklightCompensation20* pBacklightCompensation;
    struct ns3__Exposure20* pExposure;
    struct ns3__FocusConfiguration20* pFocusConfiguration;
    enum ns3__IrCutFilterMode* pIrCutFilter;
    struct ns3__WhiteBalance20* pWhiteBalance;
    struct ns3__WideDynamicRange20* pWideDynamicRange;
    pBacklightCompensation = (struct ns3__BacklightCompensation20*)soap_malloc(soap,sizeof(struct ns3__BacklightCompensation20));
    pExposure = (struct ns3__Exposure20*)soap_malloc(soap,sizeof(struct ns3__Exposure20));
    pFocusConfiguration = (struct ns3__FocusConfiguration20*)soap_malloc(soap,sizeof(struct ns3__FocusConfiguration20));
    pIrCutFilter = (enum ns3__IrCutFilterMode*)soap_malloc(soap,sizeof(enum ns3__IrCutFilterMode));
    pWhiteBalance = (struct ns3__WhiteBalance20*)soap_malloc(soap,sizeof(struct ns3__WhiteBalance20));
    pWideDynamicRange = (struct ns3__WideDynamicRange20*)soap_malloc(soap,sizeof(struct ns3__WideDynamicRange20));    
    memset(pBacklightCompensation,0,sizeof(struct ns3__BacklightCompensation20));
    memset(pExposure,0,sizeof(struct ns3__Exposure20));
    memset(pFocusConfiguration,0,sizeof(struct ns3__FocusConfiguration20)); 
    memset(pIrCutFilter,0,sizeof(enum ns3__IrCutFilterMode));
    memset(pWhiteBalance,0,sizeof(struct ns3__WhiteBalance20));
    memset(pWideDynamicRange,0,sizeof(struct ns3__WideDynamicRange20));

    //±³¹â²¹³¥
    pBacklightCompensation->Mode = ns3__BacklightCompensationMode__OFF;
    pBacklightCompensation->Level= &a10086;//0

    //ÆØ¹âÊ±¼ä
    pExposure->Mode = ns3__ExposureMode__AUTO;
    #if 0
    struct ns3__Rectangle *pWindow;
    pWindow = (struct ns3__Rectangle*)soap_malloc(soap,sizeof(struct ns3__Rectangle));
    memset(pWindow,0,sizeof(struct ns3__Rectangle));
    pWindow->bottom = &a10086;
    pWindow->left   = &a10086;
    pWindow->right  = &a10086;
    pWindow->top    = &a10086;
    enum ns3__ExposurePriority *pPriority;
    pPriority= (enum ns3__ExposurePriority*)soap_malloc(soap,sizeof(enum ns3__ExposurePriority));
    memset(pPriority,0,sizeof(enum ns3__ExposurePriority));
    *pPriority = ns3__ExposurePriority__FrameRate;
    
    pExposure->Priority = pPriority;
    pExposure->Window = pWindow;
    pExposure->MaxExposureTime = &a10086;
    pExposure->MinExposureTime = &a10086;
    pExposure->MinGain = &a10086;
    pExposure->MaxGain = &a10086;
    pExposure->MaxIris = &a10086;
    pExposure->MinIris = &a10086;
    pExposure->Gain = &a10086;
    pExposure->Iris = &a10086;
    pExposure->ExposureTime = &a10086;
    #endif

    //¾Û½¹
    pFocusConfiguration->AutoFocusMode = ns3__AutoFocusMode__MANUAL;
    #if 0
    pFocusConfiguration->DefaultSpeed = &a10086;
    pFocusConfiguration->NearLimit = &a10086;
    pFocusConfiguration->FarLimit  = &a10086;
    #endif
    //ircut filter
    *pIrCutFilter = ns3__IrCutFilterMode__AUTO;
    //°×Æ½ºâ
    pWhiteBalance->Mode = ns3__WhiteBalanceMode__AUTO;
    //pWhiteBalance->CrGain = &a10086;
    //pWhiteBalance->CbGain = &a10086;
    //¿í¶¯Ì¬·ù¶È
    pWideDynamicRange->Mode = ns3__WideDynamicMode__ON;
    pWideDynamicRange->Level= &a10086;//0
    
    struct ns3__ImagingSettings20* pImagingSettings20;
    pImagingSettings20 = (struct ns3__ImagingSettings20*)soap_malloc(soap,sizeof(struct ns3__ImagingSettings20));
    memset(pImagingSettings20,0,sizeof(struct ns3__ImagingSettings20));
    pImagingSettings20->BacklightCompensation = pBacklightCompensation;
    pImagingSettings20->Contrast = &a10086;
    pImagingSettings20->Sharpness = &a10086;
    pImagingSettings20->Brightness = &a10086;
    pImagingSettings20->ColorSaturation = &a10086;
    pImagingSettings20->Exposure = pExposure;
    pImagingSettings20->Focus = pFocusConfiguration;
    pImagingSettings20->IrCutFilter = pIrCutFilter;
    pImagingSettings20->WhiteBalance = pWhiteBalance;
    pImagingSettings20->WideDynamicRange = pWideDynamicRange;
    
    ns12__GetImagingSettingsResponse->ImagingSettings = pImagingSettings20;
    return SOAP_OK;
}

int __ns12__SetImagingSettings(struct soap* soap, struct _ns12__SetImagingSettings *ns12__SetImagingSettings, struct _ns12__SetImagingSettingsResponse *ns12__SetImagingSettingsResponse)
{
    printf("%s\n",__FUNCTION__);
    
    return SOAP_OK;
}

int __ns12__GetOptions(struct soap* soap, struct _ns12__GetOptions *ns12__GetOptions, struct _ns12__GetOptionsResponse *ns12__GetOptionsResponse)
{
    printf("%s\n",__FUNCTION__);
    
    struct ns3__ImagingOptions20* pImagingOptions;
    pImagingOptions = (struct ns3__ImagingOptions20*)soap_malloc(soap,sizeof(struct ns3__ImagingOptions20));
    memset(pImagingOptions,0,sizeof(struct ns3__ImagingOptions20));
    pImagingOptions->BacklightCompensation;
    pImagingOptions->Brightness;
    pImagingOptions->ColorSaturation;
    pImagingOptions->Contrast;
    pImagingOptions->Exposure;
    pImagingOptions->Focus;
    pImagingOptions->__sizeIrCutFilterModes;
    pImagingOptions->IrCutFilterModes;
    pImagingOptions->Sharpness;
    pImagingOptions->WideDynamicRange;
    pImagingOptions->WhiteBalance;
    
    ns12__GetOptionsResponse->ImagingOptions = pImagingOptions;
    return SOAP_OK;
}

 int  __ns12__Move(struct soap* soap, struct _ns12__Move *ns12__Move, struct _ns12__MoveResponse *ns12__MoveResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns12__Stop(struct soap* soap, struct _ns12__Stop *ns12__Stop, struct _ns12__StopResponse *ns12__StopResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns12__GetStatus(struct soap* soap, struct _ns12__GetStatus *ns12__GetStatus, struct _ns12__GetStatusResponse *ns12__GetStatusResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

int __ns12__GetMoveOptions(struct soap* soap, struct _ns12__GetMoveOptions *ns12__GetMoveOptions, struct _ns12__GetMoveOptionsResponse *ns12__GetMoveOptionsResponse)
{
    printf("%s\n",__FUNCTION__);

    struct ns3__FloatRange* pAPosition= (struct ns3__FloatRange*)soap_malloc(soap,sizeof(struct ns3__FloatRange));
    struct ns3__FloatRange* pASpeed   = (struct ns3__FloatRange*)soap_malloc(soap,sizeof(struct ns3__FloatRange));
    struct ns3__FloatRange* pCSpeed   = (struct ns3__FloatRange*)soap_malloc(soap,sizeof(struct ns3__FloatRange));
    struct ns3__FloatRange* pRDistance= (struct ns3__FloatRange*)soap_malloc(soap,sizeof(struct ns3__FloatRange));
    struct ns3__FloatRange* pRSpeed   = (struct ns3__FloatRange*)soap_malloc(soap,sizeof(struct ns3__FloatRange));
    memset(pAPosition,0,sizeof(struct ns3__FloatRange));
    memset(pASpeed   ,0,sizeof(struct ns3__FloatRange));
    memset(pCSpeed   ,0,sizeof(struct ns3__FloatRange));
    memset(pRDistance,0,sizeof(struct ns3__FloatRange));
    memset(pRSpeed   ,0,sizeof(struct ns3__FloatRange));
    pAPosition->Min = 10086;
    pAPosition->Max = 10086;
    pASpeed->Max = 10086;
    pASpeed->Min = 10086;
    
    pCSpeed->Max = 10086;
    pCSpeed->Min = 10086;

    pRDistance->Max = 10086;
    pRDistance->Min = 10086;
    pRSpeed->Max = 10086;
    pRSpeed->Min = 10086;	

    struct ns3__AbsoluteFocusOptions *pAbsolute;
	struct ns3__ContinuousFocusOptions *pContinuous;
	struct ns3__RelativeFocusOptions20 *pRelative;
    pAbsolute   = (struct ns3__AbsoluteFocusOptions*)soap_malloc(soap,sizeof(struct ns3__AbsoluteFocusOptions));
    pContinuous = (struct ns3__ContinuousFocusOptions*)soap_malloc(soap,sizeof(struct ns3__ContinuousFocusOptions));
    pRelative   = (struct ns3__RelativeFocusOptions20*)soap_malloc(soap,sizeof(struct ns3__RelativeFocusOptions20));
    memset(pAbsolute,0,sizeof(struct ns3__AbsoluteFocusOptions));
    memset(pContinuous,0,sizeof(struct ns3__ContinuousFocusOptions));
    memset(pRelative,0,sizeof(struct ns3__RelativeFocusOptions20));
    pAbsolute->Position = pAPosition;
    pAbsolute->Speed    = pASpeed;
    pContinuous->Speed  = pCSpeed;
    pRelative->Distance = pRDistance;
    pRelative->Speed    = pRSpeed;
    
    struct ns3__MoveOptions20* pMoveOptions;
    pMoveOptions = (struct ns3__MoveOptions20*)soap_malloc(soap,sizeof(struct ns3__MoveOptions20));
    memset(pMoveOptions,0,sizeof(struct ns3__MoveOptions20));
    pMoveOptions->Absolute  = pAbsolute;
    pMoveOptions->Continuous= pContinuous;
    pMoveOptions->Relative  = pRelative;
    
    ns12__GetMoveOptionsResponse->MoveOptions = pMoveOptions;
    return SOAP_OK;
}

int __ns13__GetServiceCapabilities(struct soap* soap, struct _ns13__GetServiceCapabilities *ns13__GetServiceCapabilities, struct _ns13__GetServiceCapabilitiesResponse *ns13__GetServiceCapabilitiesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

int __ns13__GetConfigurations(struct soap* soap, struct _ns13__GetConfigurations *ns13__GetConfigurations, struct _ns13__GetConfigurationsResponse *ns13__GetConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

int __ns13__GetPresets(struct soap* soap, struct _ns13__GetPresets *ns13__GetPresets, struct _ns13__GetPresetsResponse *ns13__GetPresetsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns13__SetPreset(struct soap* soap, struct _ns13__SetPreset *ns13__SetPreset, struct _ns13__SetPresetResponse *ns13__SetPresetResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns13__RemovePreset(struct soap* soap, struct _ns13__RemovePreset *ns13__RemovePreset, struct _ns13__RemovePresetResponse *ns13__RemovePresetResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns13__GotoPreset(struct soap* soap, struct _ns13__GotoPreset *ns13__GotoPreset, struct _ns13__GotoPresetResponse *ns13__GotoPresetResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

int  __ns13__GetStatus(struct soap* soap, struct _ns13__GetStatus *ns13__GetStatus, struct _ns13__GetStatusResponse *ns13__GetStatusResponse)
{
    printf("%s\n",__FUNCTION__);
    time_t rawtime; 
    time(&rawtime); 
    
    struct ns3__Vector2D *pPanTilt;
	struct ns3__Vector1D *pZoom;
    pPanTilt= (struct ns3__Vector2D*)soap_malloc(soap,sizeof(struct ns3__Vector2D));
    pZoom= (struct ns3__Vector1D*)soap_malloc(soap,sizeof(struct ns3__Vector1D));
    memset(pPanTilt,0,sizeof(struct ns3__Vector2D));
    memset(pZoom   ,0,sizeof(struct ns3__Vector1D));
    pPanTilt->x = 10086;
    pPanTilt->y = 10086;
    pPanTilt->space = "www.163.com";
    pZoom->x = 10086;
    pZoom->space = "www.163.com";
    
	struct ns3__PTZVector *pPosition;
	struct ns3__PTZMoveStatus *pMoveStatus;
    pPosition  = (struct ns3__PTZVector*)soap_malloc(soap,sizeof(struct ns3__PTZVector));
    pMoveStatus= (struct ns3__PTZMoveStatus*)soap_malloc(soap,sizeof(struct ns3__PTZMoveStatus));
    memset(pPosition,0,sizeof(struct ns3__PTZVector));
    memset(pMoveStatus,0,sizeof(struct ns3__PTZMoveStatus));
    pPosition->PanTilt= pPanTilt;
    pPosition->Zoom   = pZoom;
    pMoveStatus->PanTilt= (enum ns3__MoveStatus*)soap_malloc(soap,sizeof(enum ns3__MoveStatus));
    pMoveStatus->Zoom   = (enum ns3__MoveStatus*)soap_malloc(soap,sizeof(enum ns3__MoveStatus));
    *pMoveStatus->PanTilt= ns3__MoveStatus__MOVING;
    *pMoveStatus->Zoom   = ns3__MoveStatus__MOVING;

    struct ns3__PTZStatus* pPTZStatus;
    pPTZStatus = (struct ns3__PTZStatus*)soap_malloc(soap,sizeof(struct ns3__PTZStatus));
    memset(pPTZStatus,0,sizeof(struct ns3__PTZStatus));
    pPTZStatus->Position = pPosition;
    pPTZStatus->MoveStatus = pMoveStatus;
    pPTZStatus->Error = "Sorry! PTZ Error!";
    pPTZStatus->UtcTime = rawtime;
    pPTZStatus->__size = 1;
    
    ns13__GetStatusResponse->PTZStatus = pPTZStatus;
    return SOAP_OK;
}

 int  __ns13__GetConfiguration(struct soap* soap, struct _ns13__GetConfiguration *ns13__GetConfiguration, struct _ns13__GetConfigurationResponse *ns13__GetConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns13__GetNodes(struct soap* soap, struct _ns13__GetNodes *ns13__GetNodes, struct _ns13__GetNodesResponse *ns13__GetNodesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns13__GetNode(struct soap* soap, struct _ns13__GetNode *ns13__GetNode, struct _ns13__GetNodeResponse *ns13__GetNodeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns13__SetConfiguration(struct soap* soap, struct _ns13__SetConfiguration *ns13__SetConfiguration, struct _ns13__SetConfigurationResponse *ns13__SetConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns13__GetConfigurationOptions(struct soap* soap, struct _ns13__GetConfigurationOptions *ns13__GetConfigurationOptions, struct _ns13__GetConfigurationOptionsResponse *ns13__GetConfigurationOptionsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns13__GotoHomePosition(struct soap* soap, struct _ns13__GotoHomePosition *ns13__GotoHomePosition, struct _ns13__GotoHomePositionResponse *ns13__GotoHomePositionResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns13__SetHomePosition(struct soap* soap, struct _ns13__SetHomePosition *ns13__SetHomePosition, struct _ns13__SetHomePositionResponse *ns13__SetHomePositionResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns13__ContinuousMove(struct soap* soap, struct _ns13__ContinuousMove *ns13__ContinuousMove, struct _ns13__ContinuousMoveResponse *ns13__ContinuousMoveResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns13__RelativeMove(struct soap* soap, struct _ns13__RelativeMove *ns13__RelativeMove, struct _ns13__RelativeMoveResponse *ns13__RelativeMoveResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns13__SendAuxiliaryCommand(struct soap* soap, struct _ns13__SendAuxiliaryCommand *ns13__SendAuxiliaryCommand, struct _ns13__SendAuxiliaryCommandResponse *ns13__SendAuxiliaryCommandResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns13__AbsoluteMove(struct soap* soap, struct _ns13__AbsoluteMove *ns13__AbsoluteMove, struct _ns13__AbsoluteMoveResponse *ns13__AbsoluteMoveResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns13__Stop(struct soap* soap, struct _ns13__Stop *ns13__Stop, struct _ns13__StopResponse *ns13__StopResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns16__PullMessages(struct soap* soap, struct _ns9__PullMessages *ns9__PullMessages, struct _ns9__PullMessagesResponse *ns9__PullMessagesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns16__SetSynchronizationPoint(struct soap* soap, struct _ns9__SetSynchronizationPoint *ns9__SetSynchronizationPoint, struct _ns9__SetSynchronizationPointResponse *ns9__SetSynchronizationPointResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns17__GetServiceCapabilities(struct soap* soap, struct _ns9__GetServiceCapabilities *ns9__GetServiceCapabilities, struct _ns9__GetServiceCapabilitiesResponse *ns9__GetServiceCapabilitiesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns17__CreatePullPointSubscription(struct soap* soap, struct _ns9__CreatePullPointSubscription *ns9__CreatePullPointSubscription, struct _ns9__CreatePullPointSubscriptionResponse *ns9__CreatePullPointSubscriptionResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns17__GetEventProperties(struct soap* soap, struct _ns9__GetEventProperties *ns9__GetEventProperties, struct _ns9__GetEventPropertiesResponse *ns9__GetEventPropertiesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns18__Renew(struct soap* soap, struct _ns4__Renew *ns4__Renew, struct _ns4__RenewResponse *ns4__RenewResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns18__Unsubscribe(struct soap* soap, struct _ns4__Unsubscribe *ns4__Unsubscribe, struct _ns4__UnsubscribeResponse *ns4__UnsubscribeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns19__Subscribe(struct soap* soap, struct _ns4__Subscribe *ns4__Subscribe, struct _ns4__SubscribeResponse *ns4__SubscribeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns19__GetCurrentMessage(struct soap* soap, struct _ns4__GetCurrentMessage *ns4__GetCurrentMessage, struct _ns4__GetCurrentMessageResponse *ns4__GetCurrentMessageResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetVideoSources(struct soap* soap, struct _ns2__GetVideoSources *ns2__GetVideoSources, struct _ns2__GetVideoSourcesResponse *ns2__GetVideoSourcesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioSources(struct soap* soap, struct _ns2__GetAudioSources *ns2__GetAudioSources, struct _ns2__GetAudioSourcesResponse *ns2__GetAudioSourcesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioOutputs(struct soap* soap, struct _ns2__GetAudioOutputs *ns2__GetAudioOutputs, struct _ns2__GetAudioOutputsResponse *ns2__GetAudioOutputsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__CreateProfile(struct soap* soap, struct _ns2__CreateProfile *ns2__CreateProfile, struct _ns2__CreateProfileResponse *ns2__CreateProfileResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

int __ns2__GetProfile(struct soap* soap, struct _ns2__GetProfile *ns2__GetProfile, struct _ns2__GetProfileResponse *ns2__GetProfileResponse)
{
    printf("%s\n",__FUNCTION__);
    struct ns3__Profile *pProfile;
    pProfile = (struct ns3__Profile*)soap_malloc(soap,sizeof(struct ns3__Profile));
    memset(pProfile,0,sizeof(struct ns3__Profile));
    pProfile->Name = "Profile 0";
    pProfile->token= "1";
    
    ns2__GetProfileResponse->Profile = pProfile;
    return SOAP_OK;
}

char *pszIP[] = {"0.0.0.0"};

int __ns2__GetProfiles(struct soap* soap, struct _ns2__GetProfiles *ns2__GetProfiles, struct _ns2__GetProfilesResponse *ns2__GetProfilesResponse)
{
    printf("%s\n",__FUNCTION__);
    struct ns3__IntRectangle *pBounds;
	pBounds = (struct ns3__IntRectangle *)soap_malloc(soap,sizeof(struct ns3__IntRectangle));
	memset(pBounds, 0, sizeof(struct ns3__IntRectangle));
	pBounds->x = 0;
	pBounds->y = 0;
	pBounds->width =  1920;
	pBounds->height = 1080;
    struct ns3__VideoSourceConfiguration *pVideoSourcesConfig;
	pVideoSourcesConfig = (struct ns3__VideoSourceConfiguration *)soap_malloc(soap,sizeof(struct ns3__VideoSourceConfiguration));
	memset(pVideoSourcesConfig, 0, sizeof(struct ns3__VideoSourceConfiguration));
	pVideoSourcesConfig->Name = "stream1";
	pVideoSourcesConfig->UseCount = 0;
	pVideoSourcesConfig->token = "1";
	pVideoSourcesConfig->SourceToken = "1";
    pVideoSourcesConfig->Bounds = pBounds;

    
    // VideoEncoderConfiguration
    struct ns3__VideoResolution *pVideoResolution;
	pVideoResolution = (struct ns3__VideoResolution *)soap_malloc(soap,sizeof(struct ns3__VideoResolution));
	pVideoResolution->Width = 1920;
	pVideoResolution->Height = 1080;
	struct ns3__VideoEncoderConfiguration *pVideoEncoderConfig;
	pVideoEncoderConfig = (struct ns3__VideoEncoderConfiguration *)soap_malloc(soap,sizeof(struct ns3__VideoEncoderConfiguration));
	memset(pVideoEncoderConfig, 0, sizeof(struct ns3__VideoEncoderConfiguration));
	pVideoEncoderConfig->Name = "H.264";
	pVideoEncoderConfig->UseCount = 0;
	pVideoEncoderConfig->token = "1";
	pVideoEncoderConfig->Encoding = ns3__VideoEncoding__H264;
    pVideoEncoderConfig->Resolution = pVideoResolution;
    pVideoEncoderConfig->Quality = 50.000000;

    struct ns3__VideoRateControl *pVideoRateCtrl;
    pVideoRateCtrl= (struct ns3__VideoRateControl *)soap_malloc(soap,sizeof(struct ns3__VideoRateControl));
    memset(pVideoRateCtrl,0,sizeof(struct ns3__VideoRateControl));
    pVideoRateCtrl->FrameRateLimit = 30;
	pVideoRateCtrl->EncodingInterval=1;
	pVideoRateCtrl->BitrateLimit = 2000;
    pVideoEncoderConfig->RateControl = pVideoRateCtrl;

    struct ns3__H264Configuration *pH264Config;
    pH264Config = (struct ns3__H264Configuration *)soap_malloc(soap,sizeof(struct ns3__H264Configuration));
    memset(pH264Config,0,sizeof(struct ns3__H264Configuration));
    pH264Config->GovLength = 0;
    pH264Config->H264Profile = ns3__H264Profile__Main;
    pVideoEncoderConfig->H264 = pH264Config;

    struct ns3__MulticastConfiguration *pMulticastConfig;
    pMulticastConfig = (struct ns3__MulticastConfiguration *)soap_malloc(soap,sizeof(struct ns3__MulticastConfiguration));
    memset(pMulticastConfig,0,sizeof(struct ns3__MulticastConfiguration));

	//char *pszIP = (char *)soap_malloc(soap, 128);
	//memset(pszIP, 0, 128);
	//strcpy(pszIP, "0.0.0.0");
    
    struct ns3__IPAddress *pxAddr;
    pxAddr = (struct ns3__IPAddress *)soap_malloc(soap,sizeof(struct ns3__IPAddress));
    memset(pxAddr,0,sizeof(struct ns3__IPAddress));
    pxAddr->Type = ns3__IPType__IPv4;
    pxAddr->IPv4Address = pszIP;
    pMulticastConfig->Address  = pxAddr;
    pMulticastConfig->Port = 0;
    pMulticastConfig->TTL = 64;
    pMulticastConfig->AutoStart = xsd__boolean__false_;
    
    pVideoEncoderConfig->Multicast = pMulticastConfig;
    pVideoEncoderConfig->SessionTimeout = "PT60S";
    //Target Profile
    struct ns3__Profile *pProfile;
    pProfile = (struct ns3__Profile *)soap_malloc(soap,sizeof(struct ns3__Profile));
    memset(pProfile,0,sizeof(struct ns3__Profile));
    pProfile->Name = "Profile 0";
    pProfile->token= "1";
    pProfile->VideoSourceConfiguration = pVideoSourcesConfig;
    pProfile->VideoEncoderConfiguration= pVideoEncoderConfig;

    ns2__GetProfilesResponse->__sizeProfiles = 1;
    ns2__GetProfilesResponse->Profiles = pProfile;
    return SOAP_OK;
}

 int  __ns2__AddVideoEncoderConfiguration(struct soap* soap, struct _ns2__AddVideoEncoderConfiguration *ns2__AddVideoEncoderConfiguration, struct _ns2__AddVideoEncoderConfigurationResponse *ns2__AddVideoEncoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__AddVideoSourceConfiguration(struct soap* soap, struct _ns2__AddVideoSourceConfiguration *ns2__AddVideoSourceConfiguration, struct _ns2__AddVideoSourceConfigurationResponse *ns2__AddVideoSourceConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__AddAudioEncoderConfiguration(struct soap* soap, struct _ns2__AddAudioEncoderConfiguration *ns2__AddAudioEncoderConfiguration, struct _ns2__AddAudioEncoderConfigurationResponse *ns2__AddAudioEncoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__AddAudioSourceConfiguration(struct soap* soap, struct _ns2__AddAudioSourceConfiguration *ns2__AddAudioSourceConfiguration, struct _ns2__AddAudioSourceConfigurationResponse *ns2__AddAudioSourceConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__AddPTZConfiguration(struct soap* soap, struct _ns2__AddPTZConfiguration *ns2__AddPTZConfiguration, struct _ns2__AddPTZConfigurationResponse *ns2__AddPTZConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__AddVideoAnalyticsConfiguration(struct soap* soap, struct _ns2__AddVideoAnalyticsConfiguration *ns2__AddVideoAnalyticsConfiguration, struct _ns2__AddVideoAnalyticsConfigurationResponse *ns2__AddVideoAnalyticsConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__AddMetadataConfiguration(struct soap* soap, struct _ns2__AddMetadataConfiguration *ns2__AddMetadataConfiguration, struct _ns2__AddMetadataConfigurationResponse *ns2__AddMetadataConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__AddAudioOutputConfiguration(struct soap* soap, struct _ns2__AddAudioOutputConfiguration *ns2__AddAudioOutputConfiguration, struct _ns2__AddAudioOutputConfigurationResponse *ns2__AddAudioOutputConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__AddAudioDecoderConfiguration(struct soap* soap, struct _ns2__AddAudioDecoderConfiguration *ns2__AddAudioDecoderConfiguration, struct _ns2__AddAudioDecoderConfigurationResponse *ns2__AddAudioDecoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__RemoveVideoEncoderConfiguration(struct soap* soap, struct _ns2__RemoveVideoEncoderConfiguration *ns2__RemoveVideoEncoderConfiguration, struct _ns2__RemoveVideoEncoderConfigurationResponse *ns2__RemoveVideoEncoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__RemoveVideoSourceConfiguration(struct soap* soap, struct _ns2__RemoveVideoSourceConfiguration *ns2__RemoveVideoSourceConfiguration, struct _ns2__RemoveVideoSourceConfigurationResponse *ns2__RemoveVideoSourceConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__RemoveAudioEncoderConfiguration(struct soap* soap, struct _ns2__RemoveAudioEncoderConfiguration *ns2__RemoveAudioEncoderConfiguration, struct _ns2__RemoveAudioEncoderConfigurationResponse *ns2__RemoveAudioEncoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__RemoveAudioSourceConfiguration(struct soap* soap, struct _ns2__RemoveAudioSourceConfiguration *ns2__RemoveAudioSourceConfiguration, struct _ns2__RemoveAudioSourceConfigurationResponse *ns2__RemoveAudioSourceConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__RemovePTZConfiguration(struct soap* soap, struct _ns2__RemovePTZConfiguration *ns2__RemovePTZConfiguration, struct _ns2__RemovePTZConfigurationResponse *ns2__RemovePTZConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__RemoveVideoAnalyticsConfiguration(struct soap* soap, struct _ns2__RemoveVideoAnalyticsConfiguration *ns2__RemoveVideoAnalyticsConfiguration, struct _ns2__RemoveVideoAnalyticsConfigurationResponse *ns2__RemoveVideoAnalyticsConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__RemoveMetadataConfiguration(struct soap* soap, struct _ns2__RemoveMetadataConfiguration *ns2__RemoveMetadataConfiguration, struct _ns2__RemoveMetadataConfigurationResponse *ns2__RemoveMetadataConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__RemoveAudioOutputConfiguration(struct soap* soap, struct _ns2__RemoveAudioOutputConfiguration *ns2__RemoveAudioOutputConfiguration, struct _ns2__RemoveAudioOutputConfigurationResponse *ns2__RemoveAudioOutputConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__RemoveAudioDecoderConfiguration(struct soap* soap, struct _ns2__RemoveAudioDecoderConfiguration *ns2__RemoveAudioDecoderConfiguration, struct _ns2__RemoveAudioDecoderConfigurationResponse *ns2__RemoveAudioDecoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__DeleteProfile(struct soap* soap, struct _ns2__DeleteProfile *ns2__DeleteProfile, struct _ns2__DeleteProfileResponse *ns2__DeleteProfileResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetVideoSourceConfigurations(struct soap* soap, struct _ns2__GetVideoSourceConfigurations *ns2__GetVideoSourceConfigurations, struct _ns2__GetVideoSourceConfigurationsResponse *ns2__GetVideoSourceConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetVideoEncoderConfigurations(struct soap* soap, struct _ns2__GetVideoEncoderConfigurations *ns2__GetVideoEncoderConfigurations, struct _ns2__GetVideoEncoderConfigurationsResponse *ns2__GetVideoEncoderConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioSourceConfigurations(struct soap* soap, struct _ns2__GetAudioSourceConfigurations *ns2__GetAudioSourceConfigurations, struct _ns2__GetAudioSourceConfigurationsResponse *ns2__GetAudioSourceConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioEncoderConfigurations(struct soap* soap, struct _ns2__GetAudioEncoderConfigurations *ns2__GetAudioEncoderConfigurations, struct _ns2__GetAudioEncoderConfigurationsResponse *ns2__GetAudioEncoderConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetVideoAnalyticsConfigurations(struct soap* soap, struct _ns2__GetVideoAnalyticsConfigurations *ns2__GetVideoAnalyticsConfigurations, struct _ns2__GetVideoAnalyticsConfigurationsResponse *ns2__GetVideoAnalyticsConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetMetadataConfigurations(struct soap* soap, struct _ns2__GetMetadataConfigurations *ns2__GetMetadataConfigurations, struct _ns2__GetMetadataConfigurationsResponse *ns2__GetMetadataConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioOutputConfigurations(struct soap* soap, struct _ns2__GetAudioOutputConfigurations *ns2__GetAudioOutputConfigurations, struct _ns2__GetAudioOutputConfigurationsResponse *ns2__GetAudioOutputConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioDecoderConfigurations(struct soap* soap, struct _ns2__GetAudioDecoderConfigurations *ns2__GetAudioDecoderConfigurations, struct _ns2__GetAudioDecoderConfigurationsResponse *ns2__GetAudioDecoderConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetVideoSourceConfiguration(struct soap* soap, struct _ns2__GetVideoSourceConfiguration *ns2__GetVideoSourceConfiguration, struct _ns2__GetVideoSourceConfigurationResponse *ns2__GetVideoSourceConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetVideoEncoderConfiguration(struct soap* soap, struct _ns2__GetVideoEncoderConfiguration *ns2__GetVideoEncoderConfiguration, struct _ns2__GetVideoEncoderConfigurationResponse *ns2__GetVideoEncoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioSourceConfiguration(struct soap* soap, struct _ns2__GetAudioSourceConfiguration *ns2__GetAudioSourceConfiguration, struct _ns2__GetAudioSourceConfigurationResponse *ns2__GetAudioSourceConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioEncoderConfiguration(struct soap* soap, struct _ns2__GetAudioEncoderConfiguration *ns2__GetAudioEncoderConfiguration, struct _ns2__GetAudioEncoderConfigurationResponse *ns2__GetAudioEncoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetVideoAnalyticsConfiguration(struct soap* soap, struct _ns2__GetVideoAnalyticsConfiguration *ns2__GetVideoAnalyticsConfiguration, struct _ns2__GetVideoAnalyticsConfigurationResponse *ns2__GetVideoAnalyticsConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetMetadataConfiguration(struct soap* soap, struct _ns2__GetMetadataConfiguration *ns2__GetMetadataConfiguration, struct _ns2__GetMetadataConfigurationResponse *ns2__GetMetadataConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioOutputConfiguration(struct soap* soap, struct _ns2__GetAudioOutputConfiguration *ns2__GetAudioOutputConfiguration, struct _ns2__GetAudioOutputConfigurationResponse *ns2__GetAudioOutputConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioDecoderConfiguration(struct soap* soap, struct _ns2__GetAudioDecoderConfiguration *ns2__GetAudioDecoderConfiguration, struct _ns2__GetAudioDecoderConfigurationResponse *ns2__GetAudioDecoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetCompatibleVideoEncoderConfigurations(struct soap* soap, struct _ns2__GetCompatibleVideoEncoderConfigurations *ns2__GetCompatibleVideoEncoderConfigurations, struct _ns2__GetCompatibleVideoEncoderConfigurationsResponse *ns2__GetCompatibleVideoEncoderConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetCompatibleVideoSourceConfigurations(struct soap* soap, struct _ns2__GetCompatibleVideoSourceConfigurations *ns2__GetCompatibleVideoSourceConfigurations, struct _ns2__GetCompatibleVideoSourceConfigurationsResponse *ns2__GetCompatibleVideoSourceConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetCompatibleAudioEncoderConfigurations(struct soap* soap, struct _ns2__GetCompatibleAudioEncoderConfigurations *ns2__GetCompatibleAudioEncoderConfigurations, struct _ns2__GetCompatibleAudioEncoderConfigurationsResponse *ns2__GetCompatibleAudioEncoderConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetCompatibleAudioSourceConfigurations(struct soap* soap, struct _ns2__GetCompatibleAudioSourceConfigurations *ns2__GetCompatibleAudioSourceConfigurations, struct _ns2__GetCompatibleAudioSourceConfigurationsResponse *ns2__GetCompatibleAudioSourceConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetCompatibleVideoAnalyticsConfigurations(struct soap* soap, struct _ns2__GetCompatibleVideoAnalyticsConfigurations *ns2__GetCompatibleVideoAnalyticsConfigurations, struct _ns2__GetCompatibleVideoAnalyticsConfigurationsResponse *ns2__GetCompatibleVideoAnalyticsConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetCompatibleMetadataConfigurations(struct soap* soap, struct _ns2__GetCompatibleMetadataConfigurations *ns2__GetCompatibleMetadataConfigurations, struct _ns2__GetCompatibleMetadataConfigurationsResponse *ns2__GetCompatibleMetadataConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetCompatibleAudioOutputConfigurations(struct soap* soap, struct _ns2__GetCompatibleAudioOutputConfigurations *ns2__GetCompatibleAudioOutputConfigurations, struct _ns2__GetCompatibleAudioOutputConfigurationsResponse *ns2__GetCompatibleAudioOutputConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetCompatibleAudioDecoderConfigurations(struct soap* soap, struct _ns2__GetCompatibleAudioDecoderConfigurations *ns2__GetCompatibleAudioDecoderConfigurations, struct _ns2__GetCompatibleAudioDecoderConfigurationsResponse *ns2__GetCompatibleAudioDecoderConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__SetVideoSourceConfiguration(struct soap* soap, struct _ns2__SetVideoSourceConfiguration *ns2__SetVideoSourceConfiguration, struct _ns2__SetVideoSourceConfigurationResponse *ns2__SetVideoSourceConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__SetVideoEncoderConfiguration(struct soap* soap, struct _ns2__SetVideoEncoderConfiguration *ns2__SetVideoEncoderConfiguration, struct _ns2__SetVideoEncoderConfigurationResponse *ns2__SetVideoEncoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__SetAudioSourceConfiguration(struct soap* soap, struct _ns2__SetAudioSourceConfiguration *ns2__SetAudioSourceConfiguration, struct _ns2__SetAudioSourceConfigurationResponse *ns2__SetAudioSourceConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__SetAudioEncoderConfiguration(struct soap* soap, struct _ns2__SetAudioEncoderConfiguration *ns2__SetAudioEncoderConfiguration, struct _ns2__SetAudioEncoderConfigurationResponse *ns2__SetAudioEncoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__SetVideoAnalyticsConfiguration(struct soap* soap, struct _ns2__SetVideoAnalyticsConfiguration *ns2__SetVideoAnalyticsConfiguration, struct _ns2__SetVideoAnalyticsConfigurationResponse *ns2__SetVideoAnalyticsConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__SetMetadataConfiguration(struct soap* soap, struct _ns2__SetMetadataConfiguration *ns2__SetMetadataConfiguration, struct _ns2__SetMetadataConfigurationResponse *ns2__SetMetadataConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__SetAudioOutputConfiguration(struct soap* soap, struct _ns2__SetAudioOutputConfiguration *ns2__SetAudioOutputConfiguration, struct _ns2__SetAudioOutputConfigurationResponse *ns2__SetAudioOutputConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__SetAudioDecoderConfiguration(struct soap* soap, struct _ns2__SetAudioDecoderConfiguration *ns2__SetAudioDecoderConfiguration, struct _ns2__SetAudioDecoderConfigurationResponse *ns2__SetAudioDecoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

int __ns2__GetVideoSourceConfigurationOptions(struct soap* soap, struct _ns2__GetVideoSourceConfigurationOptions *ns2__GetVideoSourceConfigurationOptions, struct _ns2__GetVideoSourceConfigurationOptionsResponse *ns2__GetVideoSourceConfigurationOptionsResponse)
{
    printf("%s\n",__FUNCTION__);
    #if 0
    struct ns3__IntRange *HRange;
    struct ns3__IntRange *WRange;
    struct ns3__IntRange *XRange;
    struct ns3__IntRange *YRange;
    HRange = (struct ns3__IntRange*)soap_malloc(soap,sizeof(struct ns3__IntRange));
    WRange = (struct ns3__IntRange*)soap_malloc(soap,sizeof(struct ns3__IntRange));
    XRange = (struct ns3__IntRange*)soap_malloc(soap,sizeof(struct ns3__IntRange));
    YRange = (struct ns3__IntRange*)soap_malloc(soap,sizeof(struct ns3__IntRange));
    memset(HRange,0,sizeof(struct ns3__IntRange));
    memset(WRange,0,sizeof(struct ns3__IntRange));
    memset(XRange,0,sizeof(struct ns3__IntRange));
    memset(YRange,0,sizeof(struct ns3__IntRange));
    HRange->Max = 500;
    HRange->Min = 100;
    WRange->Max = 600;
    WRange->Min = 120;
    XRange->Max = 320;
    XRange->Min = 300;
    YRange->Max = 240;
    YRange->Min = 200;
    #else
    struct ns3__IntRange *pRange[4];
    int i = 0;
    for( i = 0 ; i < 4 ; i++)
    {
        pRange[i] = (struct ns3__IntRange*)soap_malloc(soap,sizeof(struct ns3__IntRange));
        memset(pRange[i++],0,sizeof(struct ns3__IntRange));
    }
    pRange[0]->Max = 1280;
    pRange[0]->Min = 600;
    pRange[1]->Max = 1920;
    pRange[1]->Min = 800;
    pRange[2]->Max = 320;
    pRange[2]->Min = 300;
    pRange[3]->Max = 240;
    pRange[3]->Min = 200;
    #endif
    
    struct ns3__IntRectangleRange *boundsRange;
    boundsRange = (struct ns3__IntRectangleRange*)soap_malloc(soap,sizeof(struct ns3__IntRectangleRange));
    memset(boundsRange,0,sizeof(struct ns3__IntRectangleRange));
    boundsRange->HeightRange = pRange[0];
    boundsRange->WidthRange = pRange[1];
    boundsRange->XRange = pRange[2];
    boundsRange->YRange = pRange[3];

    char szVideoSourceConfigOption[][6] = {"H264","JPEG","MPEG"};
    char **pVSConfigOption = NULL;
    pVSConfigOption = (char **)szVideoSourceConfigOption;
    
    struct ns3__VideoSourceConfigurationOptions *pVideoSourceConfigOption;
    pVideoSourceConfigOption = (struct ns3__VideoSourceConfigurationOptions*)soap_malloc(soap,sizeof(struct ns3__VideoSourceConfigurationOptions));
    memset(pVideoSourceConfigOption ,0, sizeof(struct ns3__VideoSourceConfigurationOptions));
    pVideoSourceConfigOption->VideoSourceTokensAvailable = pVSConfigOption;
    pVideoSourceConfigOption->BoundsRange = boundsRange;
    
    ns2__GetVideoSourceConfigurationOptionsResponse->Options = pVideoSourceConfigOption;
    return SOAP_OK;
}

int __ns2__GetVideoEncoderConfigurationOptions(struct soap* soap, struct _ns2__GetVideoEncoderConfigurationOptions *ns2__GetVideoEncoderConfigurationOptions, struct _ns2__GetVideoEncoderConfigurationOptionsResponse *ns2__GetVideoEncoderConfigurationOptionsResponse)
{
    printf("%s\n",__FUNCTION__);
    enum ns3__H264Profile* pH264Profile;
    pH264Profile = (enum ns3__H264Profile*)soap_malloc(soap,sizeof(enum ns3__H264Profile));
    memset(pH264Profile,0,sizeof(enum ns3__H264Profile));
    *pH264Profile = ns3__H264Profile__Main;

    struct ns3__VideoResolution *vResolution;
    vResolution=(struct ns3__VideoResolution *)soap_malloc(soap,sizeof(struct ns3__VideoResolution));
    memset(vResolution,0,sizeof(struct ns3__VideoResolution));
    vResolution->Height = 1080;
    vResolution->Width  = 1920;

    struct ns3__IntRange *EnIntRange;
    EnIntRange=(struct ns3__IntRange *)soap_malloc(soap,sizeof(struct ns3__IntRange));
    memset(EnIntRange,0,sizeof(struct ns3__IntRange));
    EnIntRange->Min = 1;
    EnIntRange->Max = 255;

    struct ns3__IntRange *FrameRateRange;
    FrameRateRange=(struct ns3__IntRange *)soap_malloc(soap,sizeof(struct ns3__IntRange));
    memset(FrameRateRange,0,sizeof(struct ns3__IntRange));
    FrameRateRange->Min = 30;
    FrameRateRange->Max= 30;

    struct ns3__IntRange *GovLenRange;
    GovLenRange=(struct ns3__IntRange *)soap_malloc(soap,sizeof(struct ns3__IntRange));
    memset(GovLenRange,0,sizeof(struct ns3__IntRange));
    GovLenRange->Min = 0;
    GovLenRange->Max = 254;
 
    //H264
    struct ns3__H264Options *pH264Options;
    pH264Options = (struct ns3__H264Options *)soap_malloc(soap,sizeof(struct ns3__H264Options));
    memset(pH264Options,0,sizeof(struct ns3__H264Options));
    pH264Options->__sizeH264ProfilesSupported = 1;
    pH264Options->__sizeResolutionsAvailable = 1;
    pH264Options->H264ProfilesSupported = pH264Profile;
    pH264Options->ResolutionsAvailable = vResolution;
    pH264Options->EncodingIntervalRange = EnIntRange;
    pH264Options->FrameRateRange = FrameRateRange;
    pH264Options->GovLengthRange = GovLenRange;

    //JPEG
    struct ns3__JpegOptions *pJpegOptions;
    pJpegOptions = (struct ns3__JpegOptions *)soap_malloc(soap,sizeof(struct ns3__JpegOptions));
    memset(pJpegOptions,0,sizeof(struct ns3__JpegOptions));
    pJpegOptions->__sizeResolutionsAvailable = 1;
    pJpegOptions->ResolutionsAvailable = vResolution;
    pJpegOptions->EncodingIntervalRange = EnIntRange;
    pJpegOptions->FrameRateRange = FrameRateRange;

    //MPEG
    struct ns3__Mpeg4Options* pMpeg4Options;
    pMpeg4Options = (struct ns3__Mpeg4Options*)soap_malloc(soap,sizeof(struct ns3__Mpeg4Options));
    memset(pMpeg4Options,0,sizeof(struct ns3__Mpeg4Options));
    pMpeg4Options->__sizeResolutionsAvailable = 1;
    pMpeg4Options->ResolutionsAvailable = vResolution;
    pMpeg4Options->EncodingIntervalRange= EnIntRange;
    pMpeg4Options->FrameRateRange = FrameRateRange;

    //QualityRange
    struct ns3__IntRange *pIntRange;
    pIntRange = (struct ns3__IntRange*)soap_malloc(soap,sizeof(struct ns3__IntRange));
    memset(pIntRange,0,sizeof(struct ns3__IntRange));
    pIntRange->Min = 0;
    pIntRange->Max = 100;
        
    struct ns3__VideoEncoderConfigurationOptions *pVideoEncoderConfigurationOptions;
    pVideoEncoderConfigurationOptions = (struct ns3__VideoEncoderConfigurationOptions *)soap_malloc(soap,sizeof(struct ns3__VideoEncoderConfigurationOptions));
    memset(pVideoEncoderConfigurationOptions,0,sizeof(struct ns3__VideoEncoderConfigurationOptions));
    pVideoEncoderConfigurationOptions->JPEG = pJpegOptions;
    pVideoEncoderConfigurationOptions->H264 = pH264Options;
    pVideoEncoderConfigurationOptions->MPEG4= pMpeg4Options;
    pVideoEncoderConfigurationOptions->QualityRange = pIntRange;

    ns2__GetVideoEncoderConfigurationOptionsResponse->Options = pVideoEncoderConfigurationOptions;
    return SOAP_OK;
}

 int  __ns2__GetAudioSourceConfigurationOptions(struct soap* soap, struct _ns2__GetAudioSourceConfigurationOptions *ns2__GetAudioSourceConfigurationOptions, struct _ns2__GetAudioSourceConfigurationOptionsResponse *ns2__GetAudioSourceConfigurationOptionsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioEncoderConfigurationOptions(struct soap* soap, struct _ns2__GetAudioEncoderConfigurationOptions *ns2__GetAudioEncoderConfigurationOptions, struct _ns2__GetAudioEncoderConfigurationOptionsResponse *ns2__GetAudioEncoderConfigurationOptionsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetMetadataConfigurationOptions(struct soap* soap, struct _ns2__GetMetadataConfigurationOptions *ns2__GetMetadataConfigurationOptions, struct _ns2__GetMetadataConfigurationOptionsResponse *ns2__GetMetadataConfigurationOptionsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioOutputConfigurationOptions(struct soap* soap, struct _ns2__GetAudioOutputConfigurationOptions *ns2__GetAudioOutputConfigurationOptions, struct _ns2__GetAudioOutputConfigurationOptionsResponse *ns2__GetAudioOutputConfigurationOptionsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioDecoderConfigurationOptions(struct soap* soap, struct _ns2__GetAudioDecoderConfigurationOptions *ns2__GetAudioDecoderConfigurationOptions, struct _ns2__GetAudioDecoderConfigurationOptionsResponse *ns2__GetAudioDecoderConfigurationOptionsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetGuaranteedNumberOfVideoEncoderInstances(struct soap* soap, struct _ns2__GetGuaranteedNumberOfVideoEncoderInstances *ns2__GetGuaranteedNumberOfVideoEncoderInstances, struct _ns2__GetGuaranteedNumberOfVideoEncoderInstancesResponse *ns2__GetGuaranteedNumberOfVideoEncoderInstancesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

int __ns2__GetStreamUri(struct soap* soap, struct _ns2__GetStreamUri *ns2__GetStreamUri, struct _ns2__GetStreamUriResponse *ns2__GetStreamUriResponse)
{
    printf("%s\n",__FUNCTION__);
    struct ns3__MediaUri *pMediaUri;
	pMediaUri = (struct ns3__MediaUri*)soap_malloc(soap,sizeof(struct ns3__MediaUri));
	memset(pMediaUri, 0, sizeof(struct ns3__MediaUri));
    char *rtsp_uri;
    rtsp_uri = (char*)soap_malloc(soap,128*sizeof(char));
    #if AUTO_URI_FLAG
    snprintf(rtsp_uri,128,"rtsp://%s%s",GetLocalHostIP(),"/stream1\0");
    #else
    rtsp_uri = RTSP_URI_XADDR;
    #endif
	pMediaUri->Uri= rtsp_uri;
    printf("last=%s\n",pMediaUri->Uri);
	pMediaUri->InvalidAfterConnect = xsd__boolean__false_;
	pMediaUri->InvalidAfterReboot = xsd__boolean__false_;
	pMediaUri->Timeout = "PT0S";
	
	ns2__GetStreamUriResponse->MediaUri = pMediaUri;
    return SOAP_OK;
}

 int  __ns2__StartMulticastStreaming(struct soap* soap, struct _ns2__StartMulticastStreaming *ns2__StartMulticastStreaming, struct _ns2__StartMulticastStreamingResponse *ns2__StartMulticastStreamingResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__StopMulticastStreaming(struct soap* soap, struct _ns2__StopMulticastStreaming *ns2__StopMulticastStreaming, struct _ns2__StopMulticastStreamingResponse *ns2__StopMulticastStreamingResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__SetSynchronizationPoint(struct soap* soap, struct _ns2__SetSynchronizationPoint *ns2__SetSynchronizationPoint, struct _ns2__SetSynchronizationPointResponse *ns2__SetSynchronizationPointResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetSnapshotUri(struct soap* soap, struct _ns2__GetSnapshotUri *ns2__GetSnapshotUri, struct _ns2__GetSnapshotUriResponse *ns2__GetSnapshotUriResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetServiceCapabilities(struct soap* soap, struct _ns2__GetServiceCapabilities *ns2__GetServiceCapabilities, struct _ns2__GetServiceCapabilitiesResponse *ns2__GetServiceCapabilitiesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetVideoSources_(struct soap* soap, struct _ns2__GetVideoSources *ns2__GetVideoSources, struct _ns2__GetVideoSourcesResponse *ns2__GetVideoSourcesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioSources_(struct soap* soap, struct _ns2__GetAudioSources *ns2__GetAudioSources, struct _ns2__GetAudioSourcesResponse *ns2__GetAudioSourcesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioOutputs_(struct soap* soap, struct _ns2__GetAudioOutputs *ns2__GetAudioOutputs, struct _ns2__GetAudioOutputsResponse *ns2__GetAudioOutputsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__CreateProfile_(struct soap* soap, struct _ns2__CreateProfile *ns2__CreateProfile, struct _ns2__CreateProfileResponse *ns2__CreateProfileResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetProfile_(struct soap* soap, struct _ns2__GetProfile *ns2__GetProfile, struct _ns2__GetProfileResponse *ns2__GetProfileResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetProfiles_(struct soap* soap, struct _ns2__GetProfiles *ns2__GetProfiles, struct _ns2__GetProfilesResponse *ns2__GetProfilesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__AddVideoEncoderConfiguration_(struct soap* soap, struct _ns2__AddVideoEncoderConfiguration *ns2__AddVideoEncoderConfiguration, struct _ns2__AddVideoEncoderConfigurationResponse *ns2__AddVideoEncoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__AddVideoSourceConfiguration_(struct soap* soap, struct _ns2__AddVideoSourceConfiguration *ns2__AddVideoSourceConfiguration, struct _ns2__AddVideoSourceConfigurationResponse *ns2__AddVideoSourceConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__AddAudioEncoderConfiguration_(struct soap* soap, struct _ns2__AddAudioEncoderConfiguration *ns2__AddAudioEncoderConfiguration, struct _ns2__AddAudioEncoderConfigurationResponse *ns2__AddAudioEncoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__AddAudioSourceConfiguration_(struct soap* soap, struct _ns2__AddAudioSourceConfiguration *ns2__AddAudioSourceConfiguration, struct _ns2__AddAudioSourceConfigurationResponse *ns2__AddAudioSourceConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__AddPTZConfiguration_(struct soap* soap, struct _ns2__AddPTZConfiguration *ns2__AddPTZConfiguration, struct _ns2__AddPTZConfigurationResponse *ns2__AddPTZConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__AddVideoAnalyticsConfiguration_(struct soap* soap, struct _ns2__AddVideoAnalyticsConfiguration *ns2__AddVideoAnalyticsConfiguration, struct _ns2__AddVideoAnalyticsConfigurationResponse *ns2__AddVideoAnalyticsConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__AddMetadataConfiguration_(struct soap* soap, struct _ns2__AddMetadataConfiguration *ns2__AddMetadataConfiguration, struct _ns2__AddMetadataConfigurationResponse *ns2__AddMetadataConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__AddAudioOutputConfiguration_(struct soap* soap, struct _ns2__AddAudioOutputConfiguration *ns2__AddAudioOutputConfiguration, struct _ns2__AddAudioOutputConfigurationResponse *ns2__AddAudioOutputConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__AddAudioDecoderConfiguration_(struct soap* soap, struct _ns2__AddAudioDecoderConfiguration *ns2__AddAudioDecoderConfiguration, struct _ns2__AddAudioDecoderConfigurationResponse *ns2__AddAudioDecoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__RemoveVideoEncoderConfiguration_(struct soap* soap, struct _ns2__RemoveVideoEncoderConfiguration *ns2__RemoveVideoEncoderConfiguration, struct _ns2__RemoveVideoEncoderConfigurationResponse *ns2__RemoveVideoEncoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__RemoveVideoSourceConfiguration_(struct soap* soap, struct _ns2__RemoveVideoSourceConfiguration *ns2__RemoveVideoSourceConfiguration, struct _ns2__RemoveVideoSourceConfigurationResponse *ns2__RemoveVideoSourceConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__RemoveAudioEncoderConfiguration_(struct soap* soap, struct _ns2__RemoveAudioEncoderConfiguration *ns2__RemoveAudioEncoderConfiguration, struct _ns2__RemoveAudioEncoderConfigurationResponse *ns2__RemoveAudioEncoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__RemoveAudioSourceConfiguration_(struct soap* soap, struct _ns2__RemoveAudioSourceConfiguration *ns2__RemoveAudioSourceConfiguration, struct _ns2__RemoveAudioSourceConfigurationResponse *ns2__RemoveAudioSourceConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__RemovePTZConfiguration_(struct soap* soap, struct _ns2__RemovePTZConfiguration *ns2__RemovePTZConfiguration, struct _ns2__RemovePTZConfigurationResponse *ns2__RemovePTZConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__RemoveVideoAnalyticsConfiguration_(struct soap* soap, struct _ns2__RemoveVideoAnalyticsConfiguration *ns2__RemoveVideoAnalyticsConfiguration, struct _ns2__RemoveVideoAnalyticsConfigurationResponse *ns2__RemoveVideoAnalyticsConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__RemoveMetadataConfiguration_(struct soap* soap, struct _ns2__RemoveMetadataConfiguration *ns2__RemoveMetadataConfiguration, struct _ns2__RemoveMetadataConfigurationResponse *ns2__RemoveMetadataConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__RemoveAudioOutputConfiguration_(struct soap* soap, struct _ns2__RemoveAudioOutputConfiguration *ns2__RemoveAudioOutputConfiguration, struct _ns2__RemoveAudioOutputConfigurationResponse *ns2__RemoveAudioOutputConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__RemoveAudioDecoderConfiguration_(struct soap* soap, struct _ns2__RemoveAudioDecoderConfiguration *ns2__RemoveAudioDecoderConfiguration, struct _ns2__RemoveAudioDecoderConfigurationResponse *ns2__RemoveAudioDecoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__DeleteProfile_(struct soap* soap, struct _ns2__DeleteProfile *ns2__DeleteProfile, struct _ns2__DeleteProfileResponse *ns2__DeleteProfileResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetVideoSourceConfigurations_(struct soap* soap, struct _ns2__GetVideoSourceConfigurations *ns2__GetVideoSourceConfigurations, struct _ns2__GetVideoSourceConfigurationsResponse *ns2__GetVideoSourceConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetVideoEncoderConfigurations_(struct soap* soap, struct _ns2__GetVideoEncoderConfigurations *ns2__GetVideoEncoderConfigurations, struct _ns2__GetVideoEncoderConfigurationsResponse *ns2__GetVideoEncoderConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioSourceConfigurations_(struct soap* soap, struct _ns2__GetAudioSourceConfigurations *ns2__GetAudioSourceConfigurations, struct _ns2__GetAudioSourceConfigurationsResponse *ns2__GetAudioSourceConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioEncoderConfigurations_(struct soap* soap, struct _ns2__GetAudioEncoderConfigurations *ns2__GetAudioEncoderConfigurations, struct _ns2__GetAudioEncoderConfigurationsResponse *ns2__GetAudioEncoderConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetVideoAnalyticsConfigurations_(struct soap* soap, struct _ns2__GetVideoAnalyticsConfigurations *ns2__GetVideoAnalyticsConfigurations, struct _ns2__GetVideoAnalyticsConfigurationsResponse *ns2__GetVideoAnalyticsConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetMetadataConfigurations_(struct soap* soap, struct _ns2__GetMetadataConfigurations *ns2__GetMetadataConfigurations, struct _ns2__GetMetadataConfigurationsResponse *ns2__GetMetadataConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioOutputConfigurations_(struct soap* soap, struct _ns2__GetAudioOutputConfigurations *ns2__GetAudioOutputConfigurations, struct _ns2__GetAudioOutputConfigurationsResponse *ns2__GetAudioOutputConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioDecoderConfigurations_(struct soap* soap, struct _ns2__GetAudioDecoderConfigurations *ns2__GetAudioDecoderConfigurations, struct _ns2__GetAudioDecoderConfigurationsResponse *ns2__GetAudioDecoderConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetVideoSourceConfiguration_(struct soap* soap, struct _ns2__GetVideoSourceConfiguration *ns2__GetVideoSourceConfiguration, struct _ns2__GetVideoSourceConfigurationResponse *ns2__GetVideoSourceConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetVideoEncoderConfiguration_(struct soap* soap, struct _ns2__GetVideoEncoderConfiguration *ns2__GetVideoEncoderConfiguration, struct _ns2__GetVideoEncoderConfigurationResponse *ns2__GetVideoEncoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioSourceConfiguration_(struct soap* soap, struct _ns2__GetAudioSourceConfiguration *ns2__GetAudioSourceConfiguration, struct _ns2__GetAudioSourceConfigurationResponse *ns2__GetAudioSourceConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioEncoderConfiguration_(struct soap* soap, struct _ns2__GetAudioEncoderConfiguration *ns2__GetAudioEncoderConfiguration, struct _ns2__GetAudioEncoderConfigurationResponse *ns2__GetAudioEncoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetVideoAnalyticsConfiguration_(struct soap* soap, struct _ns2__GetVideoAnalyticsConfiguration *ns2__GetVideoAnalyticsConfiguration, struct _ns2__GetVideoAnalyticsConfigurationResponse *ns2__GetVideoAnalyticsConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetMetadataConfiguration_(struct soap* soap, struct _ns2__GetMetadataConfiguration *ns2__GetMetadataConfiguration, struct _ns2__GetMetadataConfigurationResponse *ns2__GetMetadataConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioOutputConfiguration_(struct soap* soap, struct _ns2__GetAudioOutputConfiguration *ns2__GetAudioOutputConfiguration, struct _ns2__GetAudioOutputConfigurationResponse *ns2__GetAudioOutputConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioDecoderConfiguration_(struct soap* soap, struct _ns2__GetAudioDecoderConfiguration *ns2__GetAudioDecoderConfiguration, struct _ns2__GetAudioDecoderConfigurationResponse *ns2__GetAudioDecoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetCompatibleVideoEncoderConfigurations_(struct soap* soap, struct _ns2__GetCompatibleVideoEncoderConfigurations *ns2__GetCompatibleVideoEncoderConfigurations, struct _ns2__GetCompatibleVideoEncoderConfigurationsResponse *ns2__GetCompatibleVideoEncoderConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetCompatibleVideoSourceConfigurations_(struct soap* soap, struct _ns2__GetCompatibleVideoSourceConfigurations *ns2__GetCompatibleVideoSourceConfigurations, struct _ns2__GetCompatibleVideoSourceConfigurationsResponse *ns2__GetCompatibleVideoSourceConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetCompatibleAudioEncoderConfigurations_(struct soap* soap, struct _ns2__GetCompatibleAudioEncoderConfigurations *ns2__GetCompatibleAudioEncoderConfigurations, struct _ns2__GetCompatibleAudioEncoderConfigurationsResponse *ns2__GetCompatibleAudioEncoderConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetCompatibleAudioSourceConfigurations_(struct soap* soap, struct _ns2__GetCompatibleAudioSourceConfigurations *ns2__GetCompatibleAudioSourceConfigurations, struct _ns2__GetCompatibleAudioSourceConfigurationsResponse *ns2__GetCompatibleAudioSourceConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetCompatibleVideoAnalyticsConfigurations_(struct soap* soap, struct _ns2__GetCompatibleVideoAnalyticsConfigurations *ns2__GetCompatibleVideoAnalyticsConfigurations, struct _ns2__GetCompatibleVideoAnalyticsConfigurationsResponse *ns2__GetCompatibleVideoAnalyticsConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetCompatibleMetadataConfigurations_(struct soap* soap, struct _ns2__GetCompatibleMetadataConfigurations *ns2__GetCompatibleMetadataConfigurations, struct _ns2__GetCompatibleMetadataConfigurationsResponse *ns2__GetCompatibleMetadataConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetCompatibleAudioOutputConfigurations_(struct soap* soap, struct _ns2__GetCompatibleAudioOutputConfigurations *ns2__GetCompatibleAudioOutputConfigurations, struct _ns2__GetCompatibleAudioOutputConfigurationsResponse *ns2__GetCompatibleAudioOutputConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetCompatibleAudioDecoderConfigurations_(struct soap* soap, struct _ns2__GetCompatibleAudioDecoderConfigurations *ns2__GetCompatibleAudioDecoderConfigurations, struct _ns2__GetCompatibleAudioDecoderConfigurationsResponse *ns2__GetCompatibleAudioDecoderConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__SetVideoSourceConfiguration_(struct soap* soap, struct _ns2__SetVideoSourceConfiguration *ns2__SetVideoSourceConfiguration, struct _ns2__SetVideoSourceConfigurationResponse *ns2__SetVideoSourceConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__SetVideoEncoderConfiguration_(struct soap* soap, struct _ns2__SetVideoEncoderConfiguration *ns2__SetVideoEncoderConfiguration, struct _ns2__SetVideoEncoderConfigurationResponse *ns2__SetVideoEncoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__SetAudioSourceConfiguration_(struct soap* soap, struct _ns2__SetAudioSourceConfiguration *ns2__SetAudioSourceConfiguration, struct _ns2__SetAudioSourceConfigurationResponse *ns2__SetAudioSourceConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__SetAudioEncoderConfiguration_(struct soap* soap, struct _ns2__SetAudioEncoderConfiguration *ns2__SetAudioEncoderConfiguration, struct _ns2__SetAudioEncoderConfigurationResponse *ns2__SetAudioEncoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__SetVideoAnalyticsConfiguration_(struct soap* soap, struct _ns2__SetVideoAnalyticsConfiguration *ns2__SetVideoAnalyticsConfiguration, struct _ns2__SetVideoAnalyticsConfigurationResponse *ns2__SetVideoAnalyticsConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__SetMetadataConfiguration_(struct soap* soap, struct _ns2__SetMetadataConfiguration *ns2__SetMetadataConfiguration, struct _ns2__SetMetadataConfigurationResponse *ns2__SetMetadataConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__SetAudioOutputConfiguration_(struct soap* soap, struct _ns2__SetAudioOutputConfiguration *ns2__SetAudioOutputConfiguration, struct _ns2__SetAudioOutputConfigurationResponse *ns2__SetAudioOutputConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__SetAudioDecoderConfiguration_(struct soap* soap, struct _ns2__SetAudioDecoderConfiguration *ns2__SetAudioDecoderConfiguration, struct _ns2__SetAudioDecoderConfigurationResponse *ns2__SetAudioDecoderConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetVideoSourceConfigurationOptions_(struct soap* soap, struct _ns2__GetVideoSourceConfigurationOptions *ns2__GetVideoSourceConfigurationOptions, struct _ns2__GetVideoSourceConfigurationOptionsResponse *ns2__GetVideoSourceConfigurationOptionsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetVideoEncoderConfigurationOptions_(struct soap* soap, struct _ns2__GetVideoEncoderConfigurationOptions *ns2__GetVideoEncoderConfigurationOptions, struct _ns2__GetVideoEncoderConfigurationOptionsResponse *ns2__GetVideoEncoderConfigurationOptionsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioSourceConfigurationOptions_(struct soap* soap, struct _ns2__GetAudioSourceConfigurationOptions *ns2__GetAudioSourceConfigurationOptions, struct _ns2__GetAudioSourceConfigurationOptionsResponse *ns2__GetAudioSourceConfigurationOptionsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioEncoderConfigurationOptions_(struct soap* soap, struct _ns2__GetAudioEncoderConfigurationOptions *ns2__GetAudioEncoderConfigurationOptions, struct _ns2__GetAudioEncoderConfigurationOptionsResponse *ns2__GetAudioEncoderConfigurationOptionsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetMetadataConfigurationOptions_(struct soap* soap, struct _ns2__GetMetadataConfigurationOptions *ns2__GetMetadataConfigurationOptions, struct _ns2__GetMetadataConfigurationOptionsResponse *ns2__GetMetadataConfigurationOptionsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioOutputConfigurationOptions_(struct soap* soap, struct _ns2__GetAudioOutputConfigurationOptions *ns2__GetAudioOutputConfigurationOptions, struct _ns2__GetAudioOutputConfigurationOptionsResponse *ns2__GetAudioOutputConfigurationOptionsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetAudioDecoderConfigurationOptions_(struct soap* soap, struct _ns2__GetAudioDecoderConfigurationOptions *ns2__GetAudioDecoderConfigurationOptions, struct _ns2__GetAudioDecoderConfigurationOptionsResponse *ns2__GetAudioDecoderConfigurationOptionsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetGuaranteedNumberOfVideoEncoderInstances_(struct soap* soap, struct _ns2__GetGuaranteedNumberOfVideoEncoderInstances *ns2__GetGuaranteedNumberOfVideoEncoderInstances, struct _ns2__GetGuaranteedNumberOfVideoEncoderInstancesResponse *ns2__GetGuaranteedNumberOfVideoEncoderInstancesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetStreamUri_(struct soap* soap, struct _ns2__GetStreamUri *ns2__GetStreamUri, struct _ns2__GetStreamUriResponse *ns2__GetStreamUriResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__StartMulticastStreaming_(struct soap* soap, struct _ns2__StartMulticastStreaming *ns2__StartMulticastStreaming, struct _ns2__StartMulticastStreamingResponse *ns2__StartMulticastStreamingResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__StopMulticastStreaming_(struct soap* soap, struct _ns2__StopMulticastStreaming *ns2__StopMulticastStreaming, struct _ns2__StopMulticastStreamingResponse *ns2__StopMulticastStreamingResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__SetSynchronizationPoint_(struct soap* soap, struct _ns2__SetSynchronizationPoint *ns2__SetSynchronizationPoint, struct _ns2__SetSynchronizationPointResponse *ns2__SetSynchronizationPointResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns2__GetSnapshotUri_(struct soap* soap, struct _ns2__GetSnapshotUri *ns2__GetSnapshotUri, struct _ns2__GetSnapshotUriResponse *ns2__GetSnapshotUriResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns20__Notify(struct soap* soap, struct _ns4__Notify *ns4__Notify){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns21__GetMessages(struct soap* soap, struct _ns4__GetMessages *ns4__GetMessages, struct _ns4__GetMessagesResponse *ns4__GetMessagesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns21__DestroyPullPoint(struct soap* soap, struct _ns4__DestroyPullPoint *ns4__DestroyPullPoint, struct _ns4__DestroyPullPointResponse *ns4__DestroyPullPointResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns21__Notify(struct soap* soap, struct _ns4__Notify *ns4__Notify){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns22__CreatePullPoint(struct soap* soap, struct _ns4__CreatePullPoint *ns4__CreatePullPoint, struct _ns4__CreatePullPointResponse *ns4__CreatePullPointResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns23__Renew(struct soap* soap, struct _ns4__Renew *ns4__Renew, struct _ns4__RenewResponse *ns4__RenewResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns23__Unsubscribe(struct soap* soap, struct _ns4__Unsubscribe *ns4__Unsubscribe, struct _ns4__UnsubscribeResponse *ns4__UnsubscribeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns23__PauseSubscription(struct soap* soap, struct _ns4__PauseSubscription *ns4__PauseSubscription, struct _ns4__PauseSubscriptionResponse *ns4__PauseSubscriptionResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns23__ResumeSubscription(struct soap* soap, struct _ns4__ResumeSubscription *ns4__ResumeSubscription, struct _ns4__ResumeSubscriptionResponse *ns4__ResumeSubscriptionResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

int __ns8__GetDeviceInformation(struct soap* soap, struct _ns8__GetDeviceInformation *ns8__GetDeviceInformation, struct _ns8__GetDeviceInformationResponse *ns8__GetDeviceInformationResponse)
{
    printf("%s\n",__FUNCTION__);
    ns8__GetDeviceInformationResponse->Manufacturer    = "www.hunda.com";
	ns8__GetDeviceInformationResponse->Model           = "Dinion";
	ns8__GetDeviceInformationResponse->FirmwareVersion = "auto";
	ns8__GetDeviceInformationResponse->SerialNumber    = "unit0004630a96ec";
	ns8__GetDeviceInformationResponse->HardwareId      = "Hunda";
    return SOAP_OK;
}

 int  __ns8__SetSystemDateAndTime(struct soap* soap, struct _ns8__SetSystemDateAndTime *ns8__SetSystemDateAndTime, struct _ns8__SetSystemDateAndTimeResponse *ns8__SetSystemDateAndTimeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

int __ns8__GetSystemDateAndTime(
        struct soap* soap, 
        struct _ns8__GetSystemDateAndTime *ns8__GetSystemDateAndTime, 
        struct _ns8__GetSystemDateAndTimeResponse *ns8__GetSystemDateAndTimeResponse)
{
    printf("%s\n",__FUNCTION__);
    time_t rawtime; 
    struct tm *timeinfo; 
    time(&rawtime); 
    timeinfo = localtime(&rawtime);

    struct ns3__Time *mytime; 
	struct ns3__Date *mydate;
    struct ns3__DateTime *datetime;
    mytime = (struct ns3__Time*)soap_malloc(soap,sizeof(struct ns3__Time));
    mydate = (struct ns3__Date*)soap_malloc(soap,sizeof(struct ns3__Date));
    datetime=(struct ns3__DateTime*)soap_malloc(soap,sizeof(struct ns3__DateTime));
    memset(mytime,0,sizeof(struct ns3__Time));
    memset(mydate,0,sizeof(struct ns3__Date));
    memset(datetime,0,sizeof(struct ns3__DateTime));
    
    mytime->Hour = timeinfo->tm_hour;
    mytime->Minute = timeinfo->tm_min;
    mytime->Second = timeinfo->tm_sec;
    mydate->Year = timeinfo->tm_year+1900;
    mydate->Month = timeinfo->tm_mon+1;
    mydate->Day = timeinfo->tm_mday;
    datetime->Date = mydate;
    datetime->Time = mytime;
    printf("SYS DATETIME:%d-%d-%dT%d:%d:%dZ\n",mydate->Year,mydate->Month,mydate->Day,mytime->Hour,mytime->Minute,mytime->Second);
	struct ns3__SystemDateTime *systemdateAndtime;
    systemdateAndtime = (struct ns3__SystemDateTime*)soap_malloc(soap,sizeof(struct ns3__SystemDateTime));
    memset(systemdateAndtime,0, sizeof(struct ns3__SystemDateTime));
    systemdateAndtime->DateTimeType = ns3__SetDateTimeType__Manual;
    systemdateAndtime->DaylightSavings = xsd__boolean__true_;
    systemdateAndtime->LocalDateTime = datetime;
    
	ns8__GetSystemDateAndTimeResponse->SystemDateAndTime = systemdateAndtime;
	return SOAP_OK;
}

 int  __ns8__SetSystemFactoryDefault(struct soap* soap, struct _ns8__SetSystemFactoryDefault *ns8__SetSystemFactoryDefault, struct _ns8__SetSystemFactoryDefaultResponse *ns8__SetSystemFactoryDefaultResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__UpgradeSystemFirmware(struct soap* soap, struct _ns8__UpgradeSystemFirmware *ns8__UpgradeSystemFirmware, struct _ns8__UpgradeSystemFirmwareResponse *ns8__UpgradeSystemFirmwareResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SystemReboot(struct soap* soap, struct _ns8__SystemReboot *ns8__SystemReboot, struct _ns8__SystemRebootResponse *ns8__SystemRebootResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__RestoreSystem(struct soap* soap, struct _ns8__RestoreSystem *ns8__RestoreSystem, struct _ns8__RestoreSystemResponse *ns8__RestoreSystemResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetSystemBackup(struct soap* soap, struct _ns8__GetSystemBackup *ns8__GetSystemBackup, struct _ns8__GetSystemBackupResponse *ns8__GetSystemBackupResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetSystemLog(struct soap* soap, struct _ns8__GetSystemLog *ns8__GetSystemLog, struct _ns8__GetSystemLogResponse *ns8__GetSystemLogResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetSystemSupportInformation(struct soap* soap, struct _ns8__GetSystemSupportInformation *ns8__GetSystemSupportInformation, struct _ns8__GetSystemSupportInformationResponse *ns8__GetSystemSupportInformationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetScopes(struct soap* soap, struct _ns8__GetScopes *ns8__GetScopes, struct _ns8__GetScopesResponse *ns8__GetScopesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetScopes(struct soap* soap, struct _ns8__SetScopes *ns8__SetScopes, struct _ns8__SetScopesResponse *ns8__SetScopesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__AddScopes(struct soap* soap, struct _ns8__AddScopes *ns8__AddScopes, struct _ns8__AddScopesResponse *ns8__AddScopesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__RemoveScopes(struct soap* soap, struct _ns8__RemoveScopes *ns8__RemoveScopes, struct _ns8__RemoveScopesResponse *ns8__RemoveScopesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetDiscoveryMode(struct soap* soap, struct _ns8__GetDiscoveryMode *ns8__GetDiscoveryMode, struct _ns8__GetDiscoveryModeResponse *ns8__GetDiscoveryModeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetDiscoveryMode(struct soap* soap, struct _ns8__SetDiscoveryMode *ns8__SetDiscoveryMode, struct _ns8__SetDiscoveryModeResponse *ns8__SetDiscoveryModeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetRemoteDiscoveryMode(struct soap* soap, struct _ns8__GetRemoteDiscoveryMode *ns8__GetRemoteDiscoveryMode, struct _ns8__GetRemoteDiscoveryModeResponse *ns8__GetRemoteDiscoveryModeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetRemoteDiscoveryMode(struct soap* soap, struct _ns8__SetRemoteDiscoveryMode *ns8__SetRemoteDiscoveryMode, struct _ns8__SetRemoteDiscoveryModeResponse *ns8__SetRemoteDiscoveryModeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetDPAddresses(struct soap* soap, struct _ns8__GetDPAddresses *ns8__GetDPAddresses, struct _ns8__GetDPAddressesResponse *ns8__GetDPAddressesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetEndpointReference(struct soap* soap, struct _ns8__GetEndpointReference *ns8__GetEndpointReference, struct _ns8__GetEndpointReferenceResponse *ns8__GetEndpointReferenceResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetRemoteUser(struct soap* soap, struct _ns8__GetRemoteUser *ns8__GetRemoteUser, struct _ns8__GetRemoteUserResponse *ns8__GetRemoteUserResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetRemoteUser(struct soap* soap, struct _ns8__SetRemoteUser *ns8__SetRemoteUser, struct _ns8__SetRemoteUserResponse *ns8__SetRemoteUserResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetUsers(struct soap* soap, struct _ns8__GetUsers *ns8__GetUsers, struct _ns8__GetUsersResponse *ns8__GetUsersResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__CreateUsers(struct soap* soap, struct _ns8__CreateUsers *ns8__CreateUsers, struct _ns8__CreateUsersResponse *ns8__CreateUsersResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__DeleteUsers(struct soap* soap, struct _ns8__DeleteUsers *ns8__DeleteUsers, struct _ns8__DeleteUsersResponse *ns8__DeleteUsersResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetUser(struct soap* soap, struct _ns8__SetUser *ns8__SetUser, struct _ns8__SetUserResponse *ns8__SetUserResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

int __ns8__GetWsdlUrl(struct soap* soap, struct _ns8__GetWsdlUrl *ns8__GetWsdlUrl, struct _ns8__GetWsdlUrlResponse *ns8__GetWsdlUrlResponse)
{
    printf("%s\n",__FUNCTION__);
    ns8__GetWsdlUrlResponse->WsdlUrl = "www.onvif.org";
    return SOAP_OK;
}

int __ns8__GetCapabilities(struct soap* soap, struct _ns8__GetCapabilities *ns8__GetCapabilities, struct _ns8__GetCapabilitiesResponse *ns8__GetCapabilitiesResponse)
{
    printf("%s\n",__FUNCTION__);
    struct ns3__RealTimeStreamingCapabilities *RTstreamcapt;
    RTstreamcapt = (struct ns3__RealTimeStreamingCapabilities*)soap_malloc(soap,sizeof(struct ns3__RealTimeStreamingCapabilities));
    memset(RTstreamcapt,0,sizeof(struct ns3__RealTimeStreamingCapabilities));
    enum xsd__boolean * rt;
    rt = (enum xsd__boolean*)soap_malloc(soap,sizeof(enum xsd__boolean));
    memset(rt,0,sizeof(enum xsd__boolean));
    *rt = xsd__boolean__false_;
    RTstreamcapt->RTPMulticast = rt;
    RTstreamcapt->RTP_USCORETCP= rt;
    RTstreamcapt->RTP_USCORERTSP_USCORETCP= rt;

    struct ns3__MediaCapabilities *mediacapt;
    mediacapt = (struct ns3__MediaCapabilities*)soap_malloc(soap,sizeof(struct ns3__MediaCapabilities));
    memset(mediacapt,0,sizeof(struct ns3__MediaCapabilities));
    char *cap_uri;
    cap_uri = (char*)soap_malloc(soap,32*sizeof(char));
    snprintf(cap_uri,32,"http://%s:8800",GetLocalHostIP());
    printf("in capabilities Xaddr=%s\n",cap_uri);
    mediacapt->XAddr = cap_uri;
    mediacapt->StreamingCapabilities = RTstreamcapt;

    ns8__GetCapabilitiesResponse->Capabilities = (struct ns3__Capabilities*)soap_malloc(soap,sizeof(struct ns3__Capabilities));
    memset(ns8__GetCapabilitiesResponse->Capabilities,0,sizeof(struct ns3__Capabilities));
    ns8__GetCapabilitiesResponse->Capabilities->Media = mediacapt;
    return SOAP_OK;
}

 int  __ns8__SetDPAddresses(struct soap* soap, struct _ns8__SetDPAddresses *ns8__SetDPAddresses, struct _ns8__SetDPAddressesResponse *ns8__SetDPAddressesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

int __ns8__GetHostname(struct soap* soap, struct _ns8__GetHostname *ns8__GetHostname, struct _ns8__GetHostnameResponse *ns8__GetHostnameResponse)
{
    printf("%s\n",__FUNCTION__);
	struct ns3__HostnameInformation *pHostnameInfo;
    pHostnameInfo = (struct ns3__HostnameInformation *)soap_malloc(soap,sizeof(struct ns3__HostnameInformation));
    memset(pHostnameInfo,0,sizeof(struct ns3__HostnameInformation));
	pHostnameInfo->FromDHCP = xsd__boolean__false_;
	pHostnameInfo->Name = "HUNDA";
    
	ns8__GetHostnameResponse->HostnameInformation = pHostnameInfo;
    return SOAP_OK;
}

 int  __ns8__SetHostname(struct soap* soap, struct _ns8__SetHostname *ns8__SetHostname, struct _ns8__SetHostnameResponse *ns8__SetHostnameResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetDNS(struct soap* soap, struct _ns8__GetDNS *ns8__GetDNS, struct _ns8__GetDNSResponse *ns8__GetDNSResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetDNS(struct soap* soap, struct _ns8__SetDNS *ns8__SetDNS, struct _ns8__SetDNSResponse *ns8__SetDNSResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetNTP(struct soap* soap, struct _ns8__GetNTP *ns8__GetNTP, struct _ns8__GetNTPResponse *ns8__GetNTPResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetNTP(struct soap* soap, struct _ns8__SetNTP *ns8__SetNTP, struct _ns8__SetNTPResponse *ns8__SetNTPResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetDynamicDNS(struct soap* soap, struct _ns8__GetDynamicDNS *ns8__GetDynamicDNS, struct _ns8__GetDynamicDNSResponse *ns8__GetDynamicDNSResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetDynamicDNS(struct soap* soap, struct _ns8__SetDynamicDNS *ns8__SetDynamicDNS, struct _ns8__SetDynamicDNSResponse *ns8__SetDynamicDNSResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetNetworkInterfaces(struct soap* soap, struct _ns8__GetNetworkInterfaces *ns8__GetNetworkInterfaces, struct _ns8__GetNetworkInterfacesResponse *ns8__GetNetworkInterfacesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetNetworkInterfaces(struct soap* soap, struct _ns8__SetNetworkInterfaces *ns8__SetNetworkInterfaces, struct _ns8__SetNetworkInterfacesResponse *ns8__SetNetworkInterfacesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetNetworkProtocols(struct soap* soap, struct _ns8__GetNetworkProtocols *ns8__GetNetworkProtocols, struct _ns8__GetNetworkProtocolsResponse *ns8__GetNetworkProtocolsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetNetworkProtocols(struct soap* soap, struct _ns8__SetNetworkProtocols *ns8__SetNetworkProtocols, struct _ns8__SetNetworkProtocolsResponse *ns8__SetNetworkProtocolsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetNetworkDefaultGateway(struct soap* soap, struct _ns8__GetNetworkDefaultGateway *ns8__GetNetworkDefaultGateway, struct _ns8__GetNetworkDefaultGatewayResponse *ns8__GetNetworkDefaultGatewayResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetNetworkDefaultGateway(struct soap* soap, struct _ns8__SetNetworkDefaultGateway *ns8__SetNetworkDefaultGateway, struct _ns8__SetNetworkDefaultGatewayResponse *ns8__SetNetworkDefaultGatewayResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetZeroConfiguration(struct soap* soap, struct _ns8__GetZeroConfiguration *ns8__GetZeroConfiguration, struct _ns8__GetZeroConfigurationResponse *ns8__GetZeroConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetZeroConfiguration(struct soap* soap, struct _ns8__SetZeroConfiguration *ns8__SetZeroConfiguration, struct _ns8__SetZeroConfigurationResponse *ns8__SetZeroConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetIPAddressFilter(struct soap* soap, struct _ns8__GetIPAddressFilter *ns8__GetIPAddressFilter, struct _ns8__GetIPAddressFilterResponse *ns8__GetIPAddressFilterResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetIPAddressFilter(struct soap* soap, struct _ns8__SetIPAddressFilter *ns8__SetIPAddressFilter, struct _ns8__SetIPAddressFilterResponse *ns8__SetIPAddressFilterResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__AddIPAddressFilter(struct soap* soap, struct _ns8__AddIPAddressFilter *ns8__AddIPAddressFilter, struct _ns8__AddIPAddressFilterResponse *ns8__AddIPAddressFilterResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__RemoveIPAddressFilter(struct soap* soap, struct _ns8__RemoveIPAddressFilter *ns8__RemoveIPAddressFilter, struct _ns8__RemoveIPAddressFilterResponse *ns8__RemoveIPAddressFilterResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetAccessPolicy(struct soap* soap, struct _ns8__GetAccessPolicy *ns8__GetAccessPolicy, struct _ns8__GetAccessPolicyResponse *ns8__GetAccessPolicyResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetAccessPolicy(struct soap* soap, struct _ns8__SetAccessPolicy *ns8__SetAccessPolicy, struct _ns8__SetAccessPolicyResponse *ns8__SetAccessPolicyResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__CreateCertificate(struct soap* soap, struct _ns8__CreateCertificate *ns8__CreateCertificate, struct _ns8__CreateCertificateResponse *ns8__CreateCertificateResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetCertificates(struct soap* soap, struct _ns8__GetCertificates *ns8__GetCertificates, struct _ns8__GetCertificatesResponse *ns8__GetCertificatesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetCertificatesStatus(struct soap* soap, struct _ns8__GetCertificatesStatus *ns8__GetCertificatesStatus, struct _ns8__GetCertificatesStatusResponse *ns8__GetCertificatesStatusResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetCertificatesStatus(struct soap* soap, struct _ns8__SetCertificatesStatus *ns8__SetCertificatesStatus, struct _ns8__SetCertificatesStatusResponse *ns8__SetCertificatesStatusResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__DeleteCertificates(struct soap* soap, struct _ns8__DeleteCertificates *ns8__DeleteCertificates, struct _ns8__DeleteCertificatesResponse *ns8__DeleteCertificatesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetPkcs10Request(struct soap* soap, struct _ns8__GetPkcs10Request *ns8__GetPkcs10Request, struct _ns8__GetPkcs10RequestResponse *ns8__GetPkcs10RequestResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__LoadCertificates(struct soap* soap, struct _ns8__LoadCertificates *ns8__LoadCertificates, struct _ns8__LoadCertificatesResponse *ns8__LoadCertificatesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetClientCertificateMode(struct soap* soap, struct _ns8__GetClientCertificateMode *ns8__GetClientCertificateMode, struct _ns8__GetClientCertificateModeResponse *ns8__GetClientCertificateModeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetClientCertificateMode(struct soap* soap, struct _ns8__SetClientCertificateMode *ns8__SetClientCertificateMode, struct _ns8__SetClientCertificateModeResponse *ns8__SetClientCertificateModeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetRelayOutputs(struct soap* soap, struct _ns8__GetRelayOutputs *ns8__GetRelayOutputs, struct _ns8__GetRelayOutputsResponse *ns8__GetRelayOutputsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetRelayOutputSettings(struct soap* soap, struct _ns8__SetRelayOutputSettings *ns8__SetRelayOutputSettings, struct _ns8__SetRelayOutputSettingsResponse *ns8__SetRelayOutputSettingsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetRelayOutputState(struct soap* soap, struct _ns8__SetRelayOutputState *ns8__SetRelayOutputState, struct _ns8__SetRelayOutputStateResponse *ns8__SetRelayOutputStateResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SendAuxiliaryCommand(struct soap* soap, struct _ns8__SendAuxiliaryCommand *ns8__SendAuxiliaryCommand, struct _ns8__SendAuxiliaryCommandResponse *ns8__SendAuxiliaryCommandResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetCACertificates(struct soap* soap, struct _ns8__GetCACertificates *ns8__GetCACertificates, struct _ns8__GetCACertificatesResponse *ns8__GetCACertificatesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__LoadCertificateWithPrivateKey(struct soap* soap, struct _ns8__LoadCertificateWithPrivateKey *ns8__LoadCertificateWithPrivateKey, struct _ns8__LoadCertificateWithPrivateKeyResponse *ns8__LoadCertificateWithPrivateKeyResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetCertificateInformation(struct soap* soap, struct _ns8__GetCertificateInformation *ns8__GetCertificateInformation, struct _ns8__GetCertificateInformationResponse *ns8__GetCertificateInformationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__LoadCACertificates(struct soap* soap, struct _ns8__LoadCACertificates *ns8__LoadCACertificates, struct _ns8__LoadCACertificatesResponse *ns8__LoadCACertificatesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__CreateDot1XConfiguration(struct soap* soap, struct _ns8__CreateDot1XConfiguration *ns8__CreateDot1XConfiguration, struct _ns8__CreateDot1XConfigurationResponse *ns8__CreateDot1XConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetDot1XConfiguration(struct soap* soap, struct _ns8__SetDot1XConfiguration *ns8__SetDot1XConfiguration, struct _ns8__SetDot1XConfigurationResponse *ns8__SetDot1XConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetDot1XConfiguration(struct soap* soap, struct _ns8__GetDot1XConfiguration *ns8__GetDot1XConfiguration, struct _ns8__GetDot1XConfigurationResponse *ns8__GetDot1XConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetDot1XConfigurations(struct soap* soap, struct _ns8__GetDot1XConfigurations *ns8__GetDot1XConfigurations, struct _ns8__GetDot1XConfigurationsResponse *ns8__GetDot1XConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__DeleteDot1XConfiguration(struct soap* soap, struct _ns8__DeleteDot1XConfiguration *ns8__DeleteDot1XConfiguration, struct _ns8__DeleteDot1XConfigurationResponse *ns8__DeleteDot1XConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetDot11Capabilities(struct soap* soap, struct _ns8__GetDot11Capabilities *ns8__GetDot11Capabilities, struct _ns8__GetDot11CapabilitiesResponse *ns8__GetDot11CapabilitiesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetDot11Status(struct soap* soap, struct _ns8__GetDot11Status *ns8__GetDot11Status, struct _ns8__GetDot11StatusResponse *ns8__GetDot11StatusResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__ScanAvailableDot11Networks(struct soap* soap, struct _ns8__ScanAvailableDot11Networks *ns8__ScanAvailableDot11Networks, struct _ns8__ScanAvailableDot11NetworksResponse *ns8__ScanAvailableDot11NetworksResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetSystemUris(struct soap* soap, struct _ns8__GetSystemUris *ns8__GetSystemUris, struct _ns8__GetSystemUrisResponse *ns8__GetSystemUrisResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__StartFirmwareUpgrade(struct soap* soap, struct _ns8__StartFirmwareUpgrade *ns8__StartFirmwareUpgrade, struct _ns8__StartFirmwareUpgradeResponse *ns8__StartFirmwareUpgradeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__StartSystemRestore(struct soap* soap, struct _ns8__StartSystemRestore *ns8__StartSystemRestore, struct _ns8__StartSystemRestoreResponse *ns8__StartSystemRestoreResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetServices(struct soap* soap, struct _ns8__GetServices *ns8__GetServices, struct _ns8__GetServicesResponse *ns8__GetServicesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetServiceCapabilities(struct soap* soap, struct _ns8__GetServiceCapabilities *ns8__GetServiceCapabilities, struct _ns8__GetServiceCapabilitiesResponse *ns8__GetServiceCapabilitiesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

int __ns8__GetDeviceInformation_(struct soap* soap, struct _ns8__GetDeviceInformation *ns8__GetDeviceInformation, struct _ns8__GetDeviceInformationResponse *ns8__GetDeviceInformationResponse)
{
    return SOAP_OK;
}

 int  __ns8__SetSystemDateAndTime_(struct soap* soap, struct _ns8__SetSystemDateAndTime *ns8__SetSystemDateAndTime, struct _ns8__SetSystemDateAndTimeResponse *ns8__SetSystemDateAndTimeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetSystemDateAndTime_(struct soap* soap, struct _ns8__GetSystemDateAndTime *ns8__GetSystemDateAndTime, struct _ns8__GetSystemDateAndTimeResponse *ns8__GetSystemDateAndTimeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetSystemFactoryDefault_(struct soap* soap, struct _ns8__SetSystemFactoryDefault *ns8__SetSystemFactoryDefault, struct _ns8__SetSystemFactoryDefaultResponse *ns8__SetSystemFactoryDefaultResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__UpgradeSystemFirmware_(struct soap* soap, struct _ns8__UpgradeSystemFirmware *ns8__UpgradeSystemFirmware, struct _ns8__UpgradeSystemFirmwareResponse *ns8__UpgradeSystemFirmwareResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SystemReboot_(struct soap* soap, struct _ns8__SystemReboot *ns8__SystemReboot, struct _ns8__SystemRebootResponse *ns8__SystemRebootResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__RestoreSystem_(struct soap* soap, struct _ns8__RestoreSystem *ns8__RestoreSystem, struct _ns8__RestoreSystemResponse *ns8__RestoreSystemResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetSystemBackup_(struct soap* soap, struct _ns8__GetSystemBackup *ns8__GetSystemBackup, struct _ns8__GetSystemBackupResponse *ns8__GetSystemBackupResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetSystemLog_(struct soap* soap, struct _ns8__GetSystemLog *ns8__GetSystemLog, struct _ns8__GetSystemLogResponse *ns8__GetSystemLogResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetSystemSupportInformation_(struct soap* soap, struct _ns8__GetSystemSupportInformation *ns8__GetSystemSupportInformation, struct _ns8__GetSystemSupportInformationResponse *ns8__GetSystemSupportInformationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetScopes_(struct soap* soap, struct _ns8__GetScopes *ns8__GetScopes, struct _ns8__GetScopesResponse *ns8__GetScopesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetScopes_(struct soap* soap, struct _ns8__SetScopes *ns8__SetScopes, struct _ns8__SetScopesResponse *ns8__SetScopesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__AddScopes_(struct soap* soap, struct _ns8__AddScopes *ns8__AddScopes, struct _ns8__AddScopesResponse *ns8__AddScopesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__RemoveScopes_(struct soap* soap, struct _ns8__RemoveScopes *ns8__RemoveScopes, struct _ns8__RemoveScopesResponse *ns8__RemoveScopesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetDiscoveryMode_(struct soap* soap, struct _ns8__GetDiscoveryMode *ns8__GetDiscoveryMode, struct _ns8__GetDiscoveryModeResponse *ns8__GetDiscoveryModeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetDiscoveryMode_(struct soap* soap, struct _ns8__SetDiscoveryMode *ns8__SetDiscoveryMode, struct _ns8__SetDiscoveryModeResponse *ns8__SetDiscoveryModeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetRemoteDiscoveryMode_(struct soap* soap, struct _ns8__GetRemoteDiscoveryMode *ns8__GetRemoteDiscoveryMode, struct _ns8__GetRemoteDiscoveryModeResponse *ns8__GetRemoteDiscoveryModeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetRemoteDiscoveryMode_(struct soap* soap, struct _ns8__SetRemoteDiscoveryMode *ns8__SetRemoteDiscoveryMode, struct _ns8__SetRemoteDiscoveryModeResponse *ns8__SetRemoteDiscoveryModeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetDPAddresses_(struct soap* soap, struct _ns8__GetDPAddresses *ns8__GetDPAddresses, struct _ns8__GetDPAddressesResponse *ns8__GetDPAddressesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetEndpointReference_(struct soap* soap, struct _ns8__GetEndpointReference *ns8__GetEndpointReference, struct _ns8__GetEndpointReferenceResponse *ns8__GetEndpointReferenceResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetRemoteUser_(struct soap* soap, struct _ns8__GetRemoteUser *ns8__GetRemoteUser, struct _ns8__GetRemoteUserResponse *ns8__GetRemoteUserResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetRemoteUser_(struct soap* soap, struct _ns8__SetRemoteUser *ns8__SetRemoteUser, struct _ns8__SetRemoteUserResponse *ns8__SetRemoteUserResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetUsers_(struct soap* soap, struct _ns8__GetUsers *ns8__GetUsers, struct _ns8__GetUsersResponse *ns8__GetUsersResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__CreateUsers_(struct soap* soap, struct _ns8__CreateUsers *ns8__CreateUsers, struct _ns8__CreateUsersResponse *ns8__CreateUsersResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__DeleteUsers_(struct soap* soap, struct _ns8__DeleteUsers *ns8__DeleteUsers, struct _ns8__DeleteUsersResponse *ns8__DeleteUsersResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetUser_(struct soap* soap, struct _ns8__SetUser *ns8__SetUser, struct _ns8__SetUserResponse *ns8__SetUserResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetWsdlUrl_(struct soap* soap, struct _ns8__GetWsdlUrl *ns8__GetWsdlUrl, struct _ns8__GetWsdlUrlResponse *ns8__GetWsdlUrlResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetCapabilities_(struct soap* soap, struct _ns8__GetCapabilities *ns8__GetCapabilities, struct _ns8__GetCapabilitiesResponse *ns8__GetCapabilitiesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetDPAddresses_(struct soap* soap, struct _ns8__SetDPAddresses *ns8__SetDPAddresses, struct _ns8__SetDPAddressesResponse *ns8__SetDPAddressesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetHostname_(struct soap* soap, struct _ns8__GetHostname *ns8__GetHostname, struct _ns8__GetHostnameResponse *ns8__GetHostnameResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetHostname_(struct soap* soap, struct _ns8__SetHostname *ns8__SetHostname, struct _ns8__SetHostnameResponse *ns8__SetHostnameResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetHostnameFromDHCP(struct soap* soap, struct _ns8__SetHostnameFromDHCP *ns8__SetHostnameFromDHCP, struct _ns8__SetHostnameFromDHCPResponse *ns8__SetHostnameFromDHCPResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetDNS_(struct soap* soap, struct _ns8__GetDNS *ns8__GetDNS, struct _ns8__GetDNSResponse *ns8__GetDNSResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetDNS_(struct soap* soap, struct _ns8__SetDNS *ns8__SetDNS, struct _ns8__SetDNSResponse *ns8__SetDNSResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetNTP_(struct soap* soap, struct _ns8__GetNTP *ns8__GetNTP, struct _ns8__GetNTPResponse *ns8__GetNTPResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetNTP_(struct soap* soap, struct _ns8__SetNTP *ns8__SetNTP, struct _ns8__SetNTPResponse *ns8__SetNTPResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetDynamicDNS_(struct soap* soap, struct _ns8__GetDynamicDNS *ns8__GetDynamicDNS, struct _ns8__GetDynamicDNSResponse *ns8__GetDynamicDNSResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetDynamicDNS_(struct soap* soap, struct _ns8__SetDynamicDNS *ns8__SetDynamicDNS, struct _ns8__SetDynamicDNSResponse *ns8__SetDynamicDNSResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetNetworkInterfaces_(struct soap* soap, struct _ns8__GetNetworkInterfaces *ns8__GetNetworkInterfaces, struct _ns8__GetNetworkInterfacesResponse *ns8__GetNetworkInterfacesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetNetworkInterfaces_(struct soap* soap, struct _ns8__SetNetworkInterfaces *ns8__SetNetworkInterfaces, struct _ns8__SetNetworkInterfacesResponse *ns8__SetNetworkInterfacesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetNetworkProtocols_(struct soap* soap, struct _ns8__GetNetworkProtocols *ns8__GetNetworkProtocols, struct _ns8__GetNetworkProtocolsResponse *ns8__GetNetworkProtocolsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetNetworkProtocols_(struct soap* soap, struct _ns8__SetNetworkProtocols *ns8__SetNetworkProtocols, struct _ns8__SetNetworkProtocolsResponse *ns8__SetNetworkProtocolsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetNetworkDefaultGateway_(struct soap* soap, struct _ns8__GetNetworkDefaultGateway *ns8__GetNetworkDefaultGateway, struct _ns8__GetNetworkDefaultGatewayResponse *ns8__GetNetworkDefaultGatewayResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetNetworkDefaultGateway_(struct soap* soap, struct _ns8__SetNetworkDefaultGateway *ns8__SetNetworkDefaultGateway, struct _ns8__SetNetworkDefaultGatewayResponse *ns8__SetNetworkDefaultGatewayResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetZeroConfiguration_(struct soap* soap, struct _ns8__GetZeroConfiguration *ns8__GetZeroConfiguration, struct _ns8__GetZeroConfigurationResponse *ns8__GetZeroConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetZeroConfiguration_(struct soap* soap, struct _ns8__SetZeroConfiguration *ns8__SetZeroConfiguration, struct _ns8__SetZeroConfigurationResponse *ns8__SetZeroConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetIPAddressFilter_(struct soap* soap, struct _ns8__GetIPAddressFilter *ns8__GetIPAddressFilter, struct _ns8__GetIPAddressFilterResponse *ns8__GetIPAddressFilterResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetIPAddressFilter_(struct soap* soap, struct _ns8__SetIPAddressFilter *ns8__SetIPAddressFilter, struct _ns8__SetIPAddressFilterResponse *ns8__SetIPAddressFilterResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__AddIPAddressFilter_(struct soap* soap, struct _ns8__AddIPAddressFilter *ns8__AddIPAddressFilter, struct _ns8__AddIPAddressFilterResponse *ns8__AddIPAddressFilterResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__RemoveIPAddressFilter_(struct soap* soap, struct _ns8__RemoveIPAddressFilter *ns8__RemoveIPAddressFilter, struct _ns8__RemoveIPAddressFilterResponse *ns8__RemoveIPAddressFilterResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetAccessPolicy_(struct soap* soap, struct _ns8__GetAccessPolicy *ns8__GetAccessPolicy, struct _ns8__GetAccessPolicyResponse *ns8__GetAccessPolicyResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetAccessPolicy_(struct soap* soap, struct _ns8__SetAccessPolicy *ns8__SetAccessPolicy, struct _ns8__SetAccessPolicyResponse *ns8__SetAccessPolicyResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__CreateCertificate_(struct soap* soap, struct _ns8__CreateCertificate *ns8__CreateCertificate, struct _ns8__CreateCertificateResponse *ns8__CreateCertificateResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetCertificates_(struct soap* soap, struct _ns8__GetCertificates *ns8__GetCertificates, struct _ns8__GetCertificatesResponse *ns8__GetCertificatesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetCertificatesStatus_(struct soap* soap, struct _ns8__GetCertificatesStatus *ns8__GetCertificatesStatus, struct _ns8__GetCertificatesStatusResponse *ns8__GetCertificatesStatusResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetCertificatesStatus_(struct soap* soap, struct _ns8__SetCertificatesStatus *ns8__SetCertificatesStatus, struct _ns8__SetCertificatesStatusResponse *ns8__SetCertificatesStatusResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__DeleteCertificates_(struct soap* soap, struct _ns8__DeleteCertificates *ns8__DeleteCertificates, struct _ns8__DeleteCertificatesResponse *ns8__DeleteCertificatesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetPkcs10Request_(struct soap* soap, struct _ns8__GetPkcs10Request *ns8__GetPkcs10Request, struct _ns8__GetPkcs10RequestResponse *ns8__GetPkcs10RequestResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__LoadCertificates_(struct soap* soap, struct _ns8__LoadCertificates *ns8__LoadCertificates, struct _ns8__LoadCertificatesResponse *ns8__LoadCertificatesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetClientCertificateMode_(struct soap* soap, struct _ns8__GetClientCertificateMode *ns8__GetClientCertificateMode, struct _ns8__GetClientCertificateModeResponse *ns8__GetClientCertificateModeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetClientCertificateMode_(struct soap* soap, struct _ns8__SetClientCertificateMode *ns8__SetClientCertificateMode, struct _ns8__SetClientCertificateModeResponse *ns8__SetClientCertificateModeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetRelayOutputs_(struct soap* soap, struct _ns8__GetRelayOutputs *ns8__GetRelayOutputs, struct _ns8__GetRelayOutputsResponse *ns8__GetRelayOutputsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetRelayOutputSettings_(struct soap* soap, struct _ns8__SetRelayOutputSettings *ns8__SetRelayOutputSettings, struct _ns8__SetRelayOutputSettingsResponse *ns8__SetRelayOutputSettingsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetRelayOutputState_(struct soap* soap, struct _ns8__SetRelayOutputState *ns8__SetRelayOutputState, struct _ns8__SetRelayOutputStateResponse *ns8__SetRelayOutputStateResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SendAuxiliaryCommand_(struct soap* soap, struct _ns8__SendAuxiliaryCommand *ns8__SendAuxiliaryCommand, struct _ns8__SendAuxiliaryCommandResponse *ns8__SendAuxiliaryCommandResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetCACertificates_(struct soap* soap, struct _ns8__GetCACertificates *ns8__GetCACertificates, struct _ns8__GetCACertificatesResponse *ns8__GetCACertificatesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__LoadCertificateWithPrivateKey_(struct soap* soap, struct _ns8__LoadCertificateWithPrivateKey *ns8__LoadCertificateWithPrivateKey, struct _ns8__LoadCertificateWithPrivateKeyResponse *ns8__LoadCertificateWithPrivateKeyResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetCertificateInformation_(struct soap* soap, struct _ns8__GetCertificateInformation *ns8__GetCertificateInformation, struct _ns8__GetCertificateInformationResponse *ns8__GetCertificateInformationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__LoadCACertificates_(struct soap* soap, struct _ns8__LoadCACertificates *ns8__LoadCACertificates, struct _ns8__LoadCACertificatesResponse *ns8__LoadCACertificatesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__CreateDot1XConfiguration_(struct soap* soap, struct _ns8__CreateDot1XConfiguration *ns8__CreateDot1XConfiguration, struct _ns8__CreateDot1XConfigurationResponse *ns8__CreateDot1XConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__SetDot1XConfiguration_(struct soap* soap, struct _ns8__SetDot1XConfiguration *ns8__SetDot1XConfiguration, struct _ns8__SetDot1XConfigurationResponse *ns8__SetDot1XConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetDot1XConfiguration_(struct soap* soap, struct _ns8__GetDot1XConfiguration *ns8__GetDot1XConfiguration, struct _ns8__GetDot1XConfigurationResponse *ns8__GetDot1XConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetDot1XConfigurations_(struct soap* soap, struct _ns8__GetDot1XConfigurations *ns8__GetDot1XConfigurations, struct _ns8__GetDot1XConfigurationsResponse *ns8__GetDot1XConfigurationsResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__DeleteDot1XConfiguration_(struct soap* soap, struct _ns8__DeleteDot1XConfiguration *ns8__DeleteDot1XConfiguration, struct _ns8__DeleteDot1XConfigurationResponse *ns8__DeleteDot1XConfigurationResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetDot11Capabilities_(struct soap* soap, struct _ns8__GetDot11Capabilities *ns8__GetDot11Capabilities, struct _ns8__GetDot11CapabilitiesResponse *ns8__GetDot11CapabilitiesResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetDot11Status_(struct soap* soap, struct _ns8__GetDot11Status *ns8__GetDot11Status, struct _ns8__GetDot11StatusResponse *ns8__GetDot11StatusResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__ScanAvailableDot11Networks_(struct soap* soap, struct _ns8__ScanAvailableDot11Networks *ns8__ScanAvailableDot11Networks, struct _ns8__ScanAvailableDot11NetworksResponse *ns8__ScanAvailableDot11NetworksResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__GetSystemUris_(struct soap* soap, struct _ns8__GetSystemUris *ns8__GetSystemUris, struct _ns8__GetSystemUrisResponse *ns8__GetSystemUrisResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__StartFirmwareUpgrade_(struct soap* soap, struct _ns8__StartFirmwareUpgrade *ns8__StartFirmwareUpgrade, struct _ns8__StartFirmwareUpgradeResponse *ns8__StartFirmwareUpgradeResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

 int  __ns8__StartSystemRestore_(struct soap* soap, struct _ns8__StartSystemRestore *ns8__StartSystemRestore, struct _ns8__StartSystemRestoreResponse *ns8__StartSystemRestoreResponse){printf("%s\n",__FUNCTION__);return SOAP_OK;}

