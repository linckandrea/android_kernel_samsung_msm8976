/*
 * Copyright (c) 2012-2016 The Linux Foundation. All rights reserved.
 *
 * Previously licensed under the ISC license by Qualcomm Atheros, Inc.
 *
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * This file was originally distributed by Qualcomm Atheros, Inc.
 * under proprietary terms before Copyright ownership was assigned
 * to the Linux Foundation.
 */

#ifndef WLAN_QCT_WLANSAP_H
#define WLAN_QCT_WLANSAP_H

/*===========================================================================

               W L A N   S O F T A P  P A L   L A Y E R
                       E X T E R N A L  A P I


DESCRIPTION
  This file contains the external API exposed by the wlan SAP PAL layer
  module.
===========================================================================*/


/*===========================================================================

                      EDIT HISTORY FOR FILE


  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


  $Header: /cygdrive/d/Builds/M7201JSDCAAPAD52240B/WM/platform/msm7200/Src/Drivers/SD/ClientDrivers/WLAN/QCT_BTAMP_RSN/CORE/SAP/inc/sapApi.h,v 1.21 2009/03/09 08:58:26 jzmuda Exp jzmuda $ $DateTime: $ $Author: jzmuda $


when           who                what, where, why
--------    ---                 ----------------------------------------------------------
07/01/08     SAP team       Created module.

===========================================================================*/



/*===========================================================================

                          INCLUDE FILES FOR MODULE

===========================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "vos_api.h"
#include "vos_packet.h"
#include "vos_types.h"

#include "p2p_Api.h"
#include "sme_Api.h"
/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
 #ifdef __cplusplus
 extern "C" {
 #endif



/*----------------------------------------------------------------------------
 *  Defines
 * -------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
  defines and enum
  ------------------------------------------------------------------------*/

#define       MAX_SSID_LEN                 32
#define       MAX_ACL_MAC_ADDRESS          32
#define       AUTO_CHANNEL_SELECT          0
#define       MAX_ASSOC_IND_IE_LEN         255

#define       MAX_NAME_SIZE                64
#define       MAX_TEXT_SIZE                32

#define       MAX_CHANNEL_LIST_LEN         256
#ifdef WLAN_FEATURE_MBSSID
#define       VOS_MAX_NO_OF_SAP_MODE       2 // max # of SAP
#else
#define       VOS_MAX_NO_OF_SAP_MODE       1 // max # of SAP
#endif
#define       SAP_MAX_NUM_SESSION          5
#define       SAP_MAX_OBSS_STA_CNT         1 // max # of OBSS STA

/*--------------------------------------------------------------------------
  reasonCode take form 802.11 standard Table 7-22 to be passed to WLANSAP_DisassocSta api.
  ------------------------------------------------------------------------*/

typedef enum{
    eSAP_RC_RESERVED0,               /*0*/
    eSAP_RC_UNSPECIFIED,             /*1*/
    eSAP_RC_PREV_AUTH_INVALID,       /*2*/
    eSAP_RC_STA_LEFT_DEAUTH,         /*3*/
    eSAP_RC_INACTIVITY_DISASSOC,     /*4*/
    eSAP_RC_AP_CAPACITY_FULL,        /*5*/
    eSAP_RC_CLS2_FROM_NON_AUTH_STA,  /*6*/
    eSAP_RC_CLS3_FROM_NON_AUTH_STA,  /*7*/
    eSAP_RC_STA_LEFT_DISASSOC,       /*8*/
    eSAP_RC_STA_NOT_AUTH,            /*9*/
    eSAP_RC_PC_UNACCEPTABLE,         /*10*/
    eSAP_RC_SC_UNACCEPTABLE,         /*11*/
    eSAP_RC_RESERVED1,               /*12*/
    eSAP_RC_INVALID_IE,              /*13*/
    eSAP_RC_MIC_FAIL,                /*14*/
    eSAP_RC_4_WAY_HANDSHAKE_TO,      /*15*/
    eSAP_RC_GO_KEY_HANDSHAKE_TO,     /*16*/
    eSAP_RC_IE_MISMATCH,             /*17*/
    eSAP_RC_INVALID_GRP_CHIPHER,     /*18*/
    eSAP_RC_INVALID_PAIR_CHIPHER,    /*19*/
    eSAP_RC_INVALID_AKMP,            /*20*/
    eSAP_RC_UNSUPPORTED_RSN,         /*21*/
    eSAP_RC_INVALID_RSN,             /*22*/
    eSAP_RC_1X_AUTH_FAILED,          /*23*/
    eSAP_RC_CHIPER_SUITE_REJECTED,   /*24*/
}eSapReasonCode;

typedef enum {
    eSAP_ACCEPT_UNLESS_DENIED = 0,
    eSAP_DENY_UNLESS_ACCEPTED = 1,
    eSAP_SUPPORT_ACCEPT_AND_DENY = 2, /* this type is added to support both accept and deny lists at the same time */
    eSAP_ALLOW_ALL = 3, /*In this mode all MAC addresses are allowed to connect*/
} eSapMacAddrACL;

typedef enum {
    eSAP_BLACK_LIST = 0, /* List of mac addresses NOT allowed to assoc */
    eSAP_WHITE_LIST = 1, /* List of mac addresses allowed to assoc */
} eSapACLType;

typedef enum {
    ADD_STA_TO_ACL      = 0, /* cmd to add STA to access control list */
    DELETE_STA_FROM_ACL = 1, /* cmd to delete STA from access control list */
} eSapACLCmdType;

typedef enum {
    eSAP_START_BSS_EVENT = 0, /*Event sent when BSS is started*/
    eSAP_STOP_BSS_EVENT,      /*Event sent when BSS is stopped*/
    eSAP_STA_ASSOC_IND,       /* Indicate the association request to upper layers */
    eSAP_STA_ASSOC_EVENT,     /*Event sent when we have successfully associated a station and
                                upper layer neeeds to allocate a context*/
    eSAP_STA_REASSOC_EVENT,   /*Event sent when we have successfully reassociated a station and
                                upper layer neeeds to allocate a context*/
    eSAP_STA_DISASSOC_EVENT,  /*Event sent when associated a station has disassociated as a result of various conditions */
    eSAP_STA_SET_KEY_EVENT,   /*Event sent when user called WLANSAP_SetKeySta */
    eSAP_STA_DEL_KEY_EVENT,   /*Event sent when user called WLANSAP_DelKeySta */
    eSAP_STA_MIC_FAILURE_EVENT, /*Event sent whenever there is MIC failure detected */
    eSAP_ASSOC_STA_CALLBACK_EVENT,  /*Event sent when user called WLANSAP_GetAssocStations */
    eSAP_GET_WPSPBC_SESSION_EVENT,  /* Event send when user call  WLANSAP_getWpsSessionOverlap */
    eSAP_WPS_PBC_PROBE_REQ_EVENT, /* Event send on WPS PBC probe request is received */
    eSAP_REMAIN_CHAN_READY,
    eSAP_DISCONNECT_ALL_P2P_CLIENT,
    eSAP_MAC_TRIG_STOP_BSS_EVENT,
    eSAP_UNKNOWN_STA_JOIN, /* Event send when a STA in neither white list or black list tries to associate in softap mode */
    eSAP_MAX_ASSOC_EXCEEDED, /* Event send when a new STA is rejected association since softAP max assoc limit has reached */
    eSAP_CHANNEL_CHANGE_EVENT,
    eSAP_DFS_CAC_START,
    eSAP_DFS_CAC_INTERRUPTED,
    eSAP_DFS_CAC_END,
    eSAP_DFS_RADAR_DETECT,
    eSAP_DFS_NOL_GET,  /* Event sent when user need to get the DFS NOL from CNSS */
    eSAP_DFS_NOL_SET,  /* Event sent when user need to set the DFS NOL to CNSS */
    eSAP_DFS_NO_AVAILABLE_CHANNEL, /* No ch available after DFS RADAR detect */
#ifdef FEATURE_WLAN_AP_AP_ACS_OPTIMIZE
    eSAP_ACS_SCAN_SUCCESS_EVENT,
#endif
    eSAP_ACS_CHANNEL_SELECTED,
    eSAP_ECSA_CHANGE_CHAN_IND,
} eSapHddEvent;

typedef enum {
    eSAP_OPEN_SYSTEM,
    eSAP_SHARED_KEY,
    eSAP_AUTO_SWITCH
 } eSapAuthType;

typedef enum {
    eSAP_MAC_INITATED_DISASSOC = 0x10000, /*Disassociation was internally initated from CORE stack*/
    eSAP_USR_INITATED_DISASSOC /*Disassociation was internally initated from host by invoking WLANSAP_DisassocSta call*/
 } eSapDisassocReason;

/*Handle boolean over here*/
typedef enum {
    eSAP_FALSE,
    eSAP_TRUE,
}eSapBool;

typedef enum {
    eSAP_DFS_NOL_CLEAR,
    eSAP_DFS_NOL_RANDOMIZE,
}eSapDfsNolType;

/*---------------------------------------------------------------------------
SAP PAL "status" and "reason" error code defines
 ---------------------------------------------------------------------------*/
typedef enum  {
    eSAP_STATUS_SUCCESS,                 /* Success.  */
    eSAP_STATUS_FAILURE,                 /* General Failure.  */
    eSAP_START_BSS_CHANNEL_NOT_SELECTED, /* Channel not selected during intial scan.  */
    eSAP_ERROR_MAC_START_FAIL,           /* Failed to start Infra BSS */
}eSapStatus;

/*---------------------------------------------------------------------------
SAP PAL "status" and "reason" error code defines
 ---------------------------------------------------------------------------*/
typedef enum  {
    eSAP_WPSPBC_OVERLAP_IN120S,                 /* Overlap */
    eSAP_WPSPBC_NO_WPSPBC_PROBE_REQ_IN120S,     /* no WPS probe request in 120 second */
    eSAP_WPSPBC_ONE_WPSPBC_PROBE_REQ_IN120S,    /* One WPS probe request in 120 second  */
}eWPSPBCOverlap;

/*----------------------------------------------------------------------------
 *  Typedefs
 * -------------------------------------------------------------------------*/
typedef struct sap_StartBssCompleteEvent_s {
    v_U8_t  status;
    v_U8_t  operatingChannel;
    v_U16_t staId; //self StaID
    v_U8_t  sessionId; /* SoftAP SME session ID */
} tSap_StartBssCompleteEvent;

typedef struct sap_StopBssCompleteEvent_s {
    v_U8_t status;
} tSap_StopBssCompleteEvent;

typedef struct sap_StationAssocIndication_s {
    v_MACADDR_t  staMac;
    v_U8_t       assoId;
    v_U8_t       staId;
    v_U8_t       status;
    // Required for indicating the frames to upper layer
    tANI_U32     beaconLength;
    tANI_U8*     beaconPtr;
    tANI_U32     assocReqLength;
    tANI_U8*     assocReqPtr;
    tANI_BOOLEAN fWmmEnabled;
    eCsrAuthType negotiatedAuthType;
    eCsrEncryptionType negotiatedUCEncryptionType;
    eCsrEncryptionType negotiatedMCEncryptionType;
    tANI_BOOLEAN fAuthRequired;
} tSap_StationAssocIndication;

typedef struct sap_StationAssocReassocCompleteEvent_s {
    v_MACADDR_t  staMac;
    v_U8_t       staId;
    v_U8_t       status;
    v_U8_t       ies[MAX_ASSOC_IND_IE_LEN];
    v_U16_t      iesLen;
    v_U32_t      statusCode;
    eSapAuthType SapAuthType;
    v_BOOL_t     wmmEnabled;
    // Required for indicating the frames to upper layer
    tANI_U32     beaconLength;
    tANI_U8*     beaconPtr;
    tANI_U32     assocReqLength;
    tANI_U8*     assocReqPtr;
    tANI_U32     assocRespLength;
    tANI_U8*     assocRespPtr;
    tANI_U8      timingMeasCap;
    tSirSmeChanInfo chan_info;
} tSap_StationAssocReassocCompleteEvent;

typedef struct sap_StationDisassocCompleteEvent_s {
    v_MACADDR_t        staMac;
    v_U8_t             staId;    //STAID should not be used
    v_U8_t             status;
    v_U32_t            statusCode;
    eSapDisassocReason reason;
} tSap_StationDisassocCompleteEvent;

typedef struct sap_StationSetKeyCompleteEvent_s {
    v_U8_t        status;
    v_MACADDR_t   peerMacAddr;
} tSap_StationSetKeyCompleteEvent;

/*struct corresponding to SAP_STA_DEL_KEY_EVENT */
typedef struct sap_StationDeleteKeyCompleteEvent_s {
    v_U8_t status;
    v_U8_t  keyId; /* Key index */
} tSap_StationDeleteKeyCompleteEvent;

/*struct corresponding to SAP_STA_MIC_FAILURE_EVENT */
typedef struct sap_StationMICFailureEvent_s {
    v_MACADDR_t   srcMacAddr; //address used to compute MIC
    v_MACADDR_t   staMac; //taMacAddr transmitter address
    v_MACADDR_t   dstMacAddr;
    eSapBool   multicast;
    v_U8_t     IV1;            // first byte of IV
    v_U8_t     keyId;          // second byte of IV
    v_U8_t     TSC[SIR_CIPHER_SEQ_CTR_SIZE]; // sequence number

} tSap_StationMICFailureEvent;
/*Structure to return MAC address of associated stations */
typedef struct sap_AssocMacAddr_s {
    v_MACADDR_t staMac;     /*MAC address of Station that is associated*/
    v_U8_t      assocId;        /*Association ID for the station that is associated*/
    v_U8_t      staId;            /*Station Id that is allocated to the station*/
    v_U8_t      ShortGI40Mhz;
    v_U8_t      ShortGI20Mhz;
    v_U8_t      Support40Mhz;
    v_U32_t     requestedMCRate;
    tSirSupportedRates supportedRates;
} tSap_AssocMacAddr, *tpSap_AssocMacAddr;

/*struct corresponding to SAP_ASSOC_STA_CALLBACK_EVENT */
typedef struct sap_AssocStaListEvent_s {
    VOS_MODULE_ID      module; /* module id that was passed in WLANSAP_GetAssocStations API*/
    v_U8_t             noOfAssocSta;  /* Number of associated stations*/
    tpSap_AssocMacAddr pAssocStas; /*Pointer to pre allocated memory to obtain list of associated
                                    stations passed in WLANSAP_GetAssocStations API*/
} tSap_AssocStaListEvent;

typedef struct sap_GetWPSPBCSessionEvent_s {
    v_U8_t         status;
    VOS_MODULE_ID  module; /* module id that was passed in WLANSAP_GetAssocStations API*/
    v_U8_t         UUID_E[16];         // Unique identifier of the AP.
    v_MACADDR_t    addr;
    eWPSPBCOverlap wpsPBCOverlap;
} tSap_GetWPSPBCSessionEvent;

typedef struct sap_WPSPBCProbeReqEvent_s {
    v_U8_t             status;
    VOS_MODULE_ID      module; /* module id that was passed in WLANSAP_GetAssocStations API*/
    tSirWPSPBCProbeReq WPSPBCProbeReq;
} tSap_WPSPBCProbeReqEvent;

typedef struct sap_ManagementFrameInfo_s {
    tANI_U32 nFrameLength;
    tANI_U8  frameType;
    tANI_U32 rxChan;            //Channel of where packet is received
    tANI_U8 *pbFrames;         //Point to a buffer contain the beacon, assoc req, assoc rsp frame, in that order
                             //user needs to use nBeaconLength, nAssocReqLength, nAssocRspLength to desice where
                            //each frame starts and ends.
} tSap_ManagementFrameInfo;

typedef struct sap_SendActionCnf_s {
    eSapStatus actionSendSuccess;
} tSap_SendActionCnf;

typedef struct sap_UnknownSTAJoinEvent_s {
    v_MACADDR_t    macaddr;
} tSap_UnknownSTAJoinEvent;

typedef struct sap_MaxAssocExceededEvent_s {
    v_MACADDR_t    macaddr;
} tSap_MaxAssocExceededEvent;

typedef struct sap_DfsNolInfo_s {
   v_U16_t   sDfsList;       /* size of pDfsList in byte */
   v_PVOID_t pDfsList;       /* pointer to pDfsList buffer */
} tSap_DfsNolInfo;

typedef struct sap_ChSelected_s {
   uint16_t pri_ch;
   uint16_t ht_sec_ch;
   uint16_t vht_seg0_center_ch;
   uint16_t vht_seg1_center_ch;
   uint16_t ch_width;
} tSap_ChSelectedEvent;

/**
 * struct sap_ch_change_ind - channel change indication
 * @new_chan: channel to change
 */
struct sap_ch_change_ind {
	uint16_t new_chan;
};


/*
   This struct will be filled in and passed to tpWLAN_SAPEventCB that is provided during WLANSAP_StartBss call
   The event id corresponding to structure  in the union is defined in comment next to the structure
*/

typedef struct sap_Event_s {
    eSapHddEvent sapHddEventCode;
    union {
        tSap_StartBssCompleteEvent                sapStartBssCompleteEvent; /*SAP_START_BSS_EVENT*/
        tSap_StopBssCompleteEvent                 sapStopBssCompleteEvent;  /*SAP_STOP_BSS_EVENT*/
        tSap_StationAssocIndication               sapAssocIndication;       /*SAP_ASSOC_INDICATION */
        tSap_StationAssocReassocCompleteEvent     sapStationAssocReassocCompleteEvent; /*SAP_STA_ASSOC_EVENT, SAP_STA_REASSOC_EVENT*/
        tSap_StationDisassocCompleteEvent         sapStationDisassocCompleteEvent;/*SAP_STA_DISASSOC_EVENT*/
        tSap_StationSetKeyCompleteEvent           sapStationSetKeyCompleteEvent;/*SAP_STA_SET_KEY_EVENT*/
        tSap_StationDeleteKeyCompleteEvent        sapStationDeleteKeyCompleteEvent;/*SAP_STA_DEL_KEY_EVENT*/
        tSap_StationMICFailureEvent               sapStationMICFailureEvent; /*SAP_STA_MIC_FAILURE_EVENT */
        tSap_AssocStaListEvent                    sapAssocStaListEvent; /*SAP_ASSOC_STA_CALLBACK_EVENT */
        tSap_GetWPSPBCSessionEvent                sapGetWPSPBCSessionEvent; /*SAP_GET_WPSPBC_SESSION_EVENT */
        tSap_WPSPBCProbeReqEvent                  sapPBCProbeReqEvent; /*eSAP_WPS_PBC_PROBE_REQ_EVENT */
        tSap_SendActionCnf                        sapActionCnf;
        tSap_UnknownSTAJoinEvent                  sapUnknownSTAJoin; /* eSAP_UNKNOWN_STA_JOIN */
        tSap_MaxAssocExceededEvent                sapMaxAssocExceeded; /* eSAP_MAX_ASSOC_EXCEEDED */
        tSap_DfsNolInfo                           sapDfsNolInfo;    /*eSAP_DFS_NOL_XXX */
        /*eSAP_ACS_CHANNEL_SELECTED */
        tSap_ChSelectedEvent                      sapChSelected;
        struct sap_ch_change_ind                  sap_chan_cng_ind;
    } sapevt;
} tSap_Event, *tpSap_Event;


typedef __ani_attr_pre_packed struct sap_SSID {
    v_U8_t       length;
    v_U8_t       ssId[MAX_SSID_LEN];
} __ani_attr_packed tSap_SSID_t;

typedef __ani_attr_pre_packed struct sap_SSIDInfo {
    tSap_SSID_t  ssid;       /*SSID of the AP*/
    v_U8_t       ssidHidden; /*SSID shouldn't/should be broadcast in probe RSP and beacon*/
} __ani_attr_packed tSap_SSIDInfo_t;

struct sap_acs_cfg {
    /* ACS Algo Input */
    uint8_t    acs_mode;
    uint32_t    hw_mode;
    uint8_t    start_ch;
    uint8_t    end_ch;
    uint8_t    *ch_list;
    uint8_t    ch_list_count;
#ifdef FEATURE_WLAN_AP_AP_ACS_OPTIMIZE
    uint8_t    skip_scan_status;
    uint8_t    skip_scan_range1_stch;
    uint8_t    skip_scan_range1_endch;
    uint8_t    skip_scan_range2_stch;
    uint8_t    skip_scan_range2_endch;
#endif

    uint16_t   ch_width;
    /* ACS Algo Output */
    uint8_t    pri_ch;
    uint8_t    ht_sec_ch;
    uint8_t    vht_seg0_center_ch;
    uint8_t    vht_seg1_center_ch;
};


/*
 * enum sap_acs_dfs_mode- state of DFS mode
 * @ACS_DFS_MODE_NONE: DFS mode attribute is not valid
 * @ACS_DFS_MODE_ENABLE:  DFS mode is enabled
 * @ACS_DFS_MODE_DISABLE: DFS mode is disabled
 * @ACS_DFS_MODE_DEPRIORITIZE: Deprioritize DFS channels in scanning
 */
enum  sap_acs_dfs_mode {
	ACS_DFS_MODE_NONE,
	ACS_DFS_MODE_ENABLE,
	ACS_DFS_MODE_DISABLE,
	ACS_DFS_MODE_DEPRIORITIZE
};

typedef struct sap_Config {
    tSap_SSIDInfo_t SSIDinfo;
    eCsrPhyMode     SapHw_mode; /* Wireless Mode */
    eSapMacAddrACL  SapMacaddr_acl;
    v_MACADDR_t     accept_mac[MAX_ACL_MAC_ADDRESS]; /* MAC filtering */
    v_BOOL_t        ieee80211d;      /*Specify if 11D is enabled or disabled*/
    v_BOOL_t        protEnabled;     /*Specify if protection is enabled or disabled*/
    v_BOOL_t        obssProtEnabled; /*Specify if OBSS protection is enabled or disabled*/
    v_MACADDR_t     deny_mac[MAX_ACL_MAC_ADDRESS]; /* MAC filtering */
    v_MACADDR_t     self_macaddr; //self macaddress or BSSID

    v_U8_t          channel;         /* Operation channel */
    uint8_t         sec_ch;
    uint16_t         vht_channel_width;
    uint16_t         ch_width_orig;
    v_U8_t          max_num_sta;     /* maximum number of STAs in station table */
    v_U8_t          dtim_period;     /* dtim interval */
    v_U8_t          num_accept_mac;
    v_U8_t          num_deny_mac;
    /* Max ie length 255 * 2(WPA+RSN) + 2 bytes(vendor specific ID) * 2 */
    v_U8_t          RSNWPAReqIE[(SIR_MAC_MAX_IE_LENGTH * 2) + 4];
    v_U8_t          countryCode[WNI_CFG_COUNTRY_CODE_LEN];  //it is ignored if [0] is 0.
    v_U8_t          RSNAuthType;
    v_U8_t          RSNEncryptType;
    v_U8_t          mcRSNEncryptType;
    eSapAuthType    authType;
    v_BOOL_t        privacy;
    v_BOOL_t        UapsdEnable;
    v_BOOL_t        fwdWPSPBCProbeReq;
    v_U8_t          wps_state; // 0 - disabled, 1 - not configured , 2 - configured

    v_U16_t         ht_capab;
    v_U16_t         RSNWPAReqIELength;   //The byte count in the pWPAReqIE

    v_U32_t         beacon_int;     /* Beacon Interval */
    v_U32_t         ap_table_max_size;
    v_U32_t         ap_table_expiration_time;
    v_U32_t         ht_op_mode_fixed;
    tVOS_CON_MODE   persona; /*Tells us which persona it is GO or AP for now*/
    v_U8_t          disableDFSChSwitch;
    v_U8_t          enable_radar_war;
    eCsrBand        scanBandPreference;
    v_BOOL_t        enOverLapCh;
    v_U16_t         acsBandSwitchThreshold;
    struct sap_acs_cfg acs_cfg;
#ifdef WLAN_FEATURE_11W
    v_BOOL_t        mfpRequired;
    v_BOOL_t        mfpCapable;
#endif
#ifdef FEATURE_WLAN_MCC_TO_SCC_SWITCH
    v_U8_t          cc_switch_mode;
#endif

    v_U16_t    probeRespIEsBufferLen;
    v_PVOID_t  pProbeRespIEsBuffer; /* buffer for addn ies comes from hostapd*/

    v_U16_t    assocRespIEsLen;
    v_PVOID_t  pAssocRespIEsBuffer; /* buffer for addn ies comes from hostapd*/

    v_U16_t    probeRespBcnIEsLen;
    v_PVOID_t  pProbeRespBcnIEsBuffer; /* buffer for addn ies comes from hostapd*/
    uint8_t   sap_dot11mc;      /* Specify if 11MC is enabled or disabled*/
    enum sap_acs_dfs_mode acs_dfs_mode;
} tsap_Config_t;

#ifdef FEATURE_WLAN_AP_AP_ACS_OPTIMIZE
typedef enum {
    eSAP_DO_NEW_ACS_SCAN,
    eSAP_DO_PAR_ACS_SCAN,
    eSAP_SKIP_ACS_SCAN
} tSap_skip_acs_scan;
#endif

typedef enum {
     eSAP_WPS_PROBE_RSP_IE,
    eSAP_WPS_BEACON_IE,
    eSAP_WPS_ASSOC_RSP_IE
} eSapWPSIE_CODE;

typedef struct sSapName {
    v_U8_t num_name;
    v_U8_t name[MAX_NAME_SIZE];
} tSapName;

typedef struct sSapText {
    v_U8_t num_text;
    v_U8_t text[MAX_TEXT_SIZE];
} tSapText;

typedef enum
{
    eSAP_DFS_DO_NOT_SKIP_CAC,
    eSAP_DFS_SKIP_CAC
} eSapDfsCACState_t;

typedef enum
{
    eSAP_DFS_CHANNEL_USABLE,
    eSAP_DFS_CHANNEL_AVAILABLE,
    eSAP_DFS_CHANNEL_UNAVAILABLE
} eSapDfsChanStatus_t;

typedef struct sSapDfsNolInfo
{
    v_U8_t              dfs_channel_number;
    eSapDfsChanStatus_t radar_status_flag;
    v_U64_t             radar_found_timestamp;
} tSapDfsNolInfo;

typedef struct sSapDfsInfo
{
    vos_timer_t         sap_dfs_cac_timer;
    v_U8_t              sap_radar_found_status;
    /*
     * New channel to move to when a  Radar is
     * detected on current Channel
     */
    v_U8_t              target_channel;
    v_U8_t              last_radar_found_channel;
    v_U8_t              ignore_cac;
    eSapDfsCACState_t   cac_state;
    v_U8_t              user_provided_target_channel;

    /* Requests for Channel Switch Announcement IE
     * generation and transmission
     */
    v_U8_t              csaIERequired;
    v_U8_t              numCurrentRegDomainDfsChannels;
    tSapDfsNolInfo      sapDfsChannelNolList[NUM_5GHZ_CHANNELS];
    v_U8_t              is_dfs_cac_timer_running;
    /*
     * New channel width and new channel bonding mode
     * will only be updated via channel fallback mechanism
     */
    tANI_U8             orig_cbMode;
    tANI_U8             orig_chanWidth;
    tANI_U8             new_chanWidth;
    tANI_U8             new_cbMode;

    /*
     * INI param to enable/disable SAP W53
     * channel operation.
     */
    v_U8_t              is_dfs_w53_disabled;

    /*
     * sap_operating_channel_location holds SAP indoor,
     * outdoor location information. Currently, if this
     * param is  set this Indoor/outdoor channel interop
     * restriction will only be implemented for JAPAN
     * regulatory domain.
     *
     * 0 - Indicates that location unknown
     * (or) SAP Indoor/outdoor interop is allowed
     *
     * 1 - Indicates device is operating on Indoor channels
     * and SAP cannot pick next random channel from outdoor
     * list of channels when a radar is found on current operating
     * DFS channel.
     *
     * 2 - Indicates device is operating on Outdoor Channels
     * and SAP cannot pick next random channel from indoor
     * list of channels when a radar is found on current
     * operating DFS channel.
     */
    v_U8_t              sap_operating_chan_preferred_location;

    /*
     * Flag to indicate if DFS test mode is enabled and
     * channel switch is disabled.
     */
    v_U8_t              disable_dfs_ch_switch;
    v_U8_t              sap_enable_radar_war;
    uint16_t tx_leakage_threshold;
} tSapDfsInfo;

typedef struct tagSapCtxList
{
    v_U8_t              sessionID;
    v_VOID_t*           pSapContext;
    tVOS_CON_MODE       sapPersona;
} tSapCtxList, tpSapCtxList;

typedef struct tagSapStruct
{
    //Information Required for SAP DFS Master mode
    tSapDfsInfo         SapDfsInfo;
    tSapCtxList         sapCtxList[SAP_MAX_NUM_SESSION];
#ifdef FEATURE_AP_MCC_CH_AVOIDANCE
    bool sap_channel_avoidance;
#endif /* FEATURE_AP_MCC_CH_AVOIDANCE */
    bool enable_dfs_phy_error_logs;
} tSapStruct, *tpSapStruct;

#define WPS_PROBRSP_VER_PRESENT                          0x00000001
#define WPS_PROBRSP_STATE_PRESENT                        0x00000002
#define WPS_PROBRSP_APSETUPLOCK_PRESENT                  0x00000004
#define WPS_PROBRSP_SELECTEDREGISTRA_PRESENT             0x00000008
#define WPS_PROBRSP_DEVICEPASSWORDID_PRESENT             0x00000010
#define WPS_PROBRSP_SELECTEDREGISTRACFGMETHOD_PRESENT    0x00000020
#define WPS_PROBRSP_RESPONSETYPE_PRESENT                 0x00000040
#define WPS_PROBRSP_UUIDE_PRESENT                        0x00000080
#define WPS_PROBRSP_MANUFACTURE_PRESENT                  0x00000100
#define WPS_PROBRSP_MODELNAME_PRESENT                    0x00000200
#define WPS_PROBRSP_MODELNUMBER_PRESENT                  0x00000400
#define WPS_PROBRSP_SERIALNUMBER_PRESENT                 0x00000800
#define WPS_PROBRSP_PRIMARYDEVICETYPE_PRESENT            0x00001000
#define WPS_PROBRSP_DEVICENAME_PRESENT                   0x00002000
#define WPS_PROBRSP_CONFIGMETHODS_PRESENT                0x00004000
#define WPS_PROBRSP_RF_BANDS_PRESENT                     0x00008000

typedef struct sap_WPSProbeRspIE_s {
    v_U32_t     FieldPresent;
    v_U32_t     Version;           // Version. 0x10 = version 1.0, 0x11 = etc.
    v_U32_t     wpsState;          // 1 = unconfigured, 2 = configured.
    v_BOOL_t    APSetupLocked;     // Must be included if value is TRUE
    v_BOOL_t    SelectedRegistra;  //BOOL:  indicates if the user has recently activated a Registrar to add an Enrollee.
    v_U16_t     DevicePasswordID;  // Device Password ID
    v_U16_t     SelectedRegistraCfgMethod; // Selected Registrar config method
    v_U8_t      ResponseType;      // Response type
    v_U8_t      UUID_E[16];         // Unique identifier of the AP.
    tSapName    Manufacture;
    tSapText    ModelName;
    tSapText    ModelNumber;
    tSapText    SerialNumber;
    v_U32_t     PrimaryDeviceCategory ; // Device Category ID: 1Computer, 2Input Device, ...
    v_U8_t      PrimaryDeviceOUI[4] ; // Vendor specific OUI for Device Sub Category
    v_U32_t     DeviceSubCategory ; // Device Sub Category ID: 1-PC, 2-Server if Device Category ID is computer
    tSapText    DeviceName;
    v_U16_t    ConfigMethod;     // Configuaration method
    v_U8_t    RFBand;           // RF bands available on the AP
} tSap_WPSProbeRspIE;

#define WPS_BEACON_VER_PRESENT                         0x00000001
#define WPS_BEACON_STATE_PRESENT                       0x00000002
#define WPS_BEACON_APSETUPLOCK_PRESENT                 0x00000004
#define WPS_BEACON_SELECTEDREGISTRA_PRESENT            0x00000008
#define WPS_BEACON_DEVICEPASSWORDID_PRESENT            0x00000010
#define WPS_BEACON_SELECTEDREGISTRACFGMETHOD_PRESENT   0x00000020
#define WPS_BEACON_UUIDE_PRESENT                       0x00000080
#define WPS_BEACON_RF_BANDS_PRESENT                    0x00000100

typedef struct sap_WPSBeaconIE_s {
    v_U32_t  FieldPresent;
    v_U32_t  Version;           // Version. 0x10 = version 1.0, 0x11 = etc.
    v_U32_t  wpsState;          // 1 = unconfigured, 2 = configured.
    v_BOOL_t APSetupLocked;     // Must be included if value is TRUE
    v_BOOL_t SelectedRegistra;  //BOOL:  indicates if the user has recently activated a Registrar to add an Enrollee.
    v_U16_t  DevicePasswordID;  // Device Password ID
    v_U16_t  SelectedRegistraCfgMethod; // Selected Registrar config method
    v_U8_t   UUID_E[16];        // Unique identifier of the AP.
    v_U8_t   RFBand;           // RF bands available on the AP
} tSap_WPSBeaconIE;

#define WPS_ASSOCRSP_VER_PRESENT             0x00000001
#define WPS_ASSOCRSP_RESPONSETYPE_PRESENT    0x00000002

typedef struct sap_WPSAssocRspIE_s {
   v_U32_t FieldPresent;
   v_U32_t Version;
   v_U8_t ResposeType;
} tSap_WPSAssocRspIE;

typedef struct sap_WPSIE_s {
    eSapWPSIE_CODE sapWPSIECode;
    union {
               tSap_WPSProbeRspIE  sapWPSProbeRspIE;    /*WPS Set Probe Respose IE*/
               tSap_WPSBeaconIE    sapWPSBeaconIE;      /*WPS Set Beacon IE*/
               tSap_WPSAssocRspIE  sapWPSAssocRspIE;    /*WPS Set Assoc Response IE*/
    } sapwpsie;
} tSap_WPSIE, *tpSap_WPSIE;

#ifdef WLANTL_DEBUG
#define MAX_RATE_INDEX      136
#define MAX_NUM_RSSI        100
#define MAX_RSSI_INTERVAL     5
#endif

typedef struct sap_SoftapStats_s {
   v_U32_t txUCFcnt;
   v_U32_t txMCFcnt;
   v_U32_t txBCFcnt;
   v_U32_t txUCBcnt;
   v_U32_t txMCBcnt;
   v_U32_t txBCBcnt;
   v_U32_t rxUCFcnt;
   v_U32_t rxMCFcnt;
   v_U32_t rxBCFcnt;
   v_U32_t rxUCBcnt;
   v_U32_t rxMCBcnt;
   v_U32_t rxBCBcnt;
   v_U32_t rxBcnt;
   v_U32_t rxBcntCRCok;
   v_U32_t rxRate;
#ifdef WLANTL_DEBUG
   v_U32_t pktCounterRateIdx[MAX_RATE_INDEX];
   v_U32_t pktCounterRssi[MAX_NUM_RSSI];
#endif
} tSap_SoftapStats, *tpSap_SoftapStats;

int sapSetPreferredChannel
(
#ifdef WLAN_FEATURE_MBSSID
    v_PVOID_t sapContext,
#endif
    tANI_U8* ptr
);

/* Channel/Frequency table */
extern const tRfChannelProps rfChannels[NUM_RF_CHANNELS];

#ifdef FEATURE_WLAN_CH_AVOID
/* Store channel safety information */
typedef struct
{
   v_U16_t   channelNumber;
   v_BOOL_t  isSafe;
} sapSafeChannelType;
#endif //FEATURE_WLAN_CH_AVOID

#ifdef WLAN_FEATURE_MBSSID
void sapCleanupChannelList(v_PVOID_t sapContext);
#else
void sapCleanupChannelList(void);
#endif

void sapCleanupAllChannelList(void);

/*==========================================================================
  FUNCTION    WLANSAP_Set_WpsIe

  DESCRIPTION
    This api function provides for Ap App/HDD to set WPS IE.

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
  pvosGCtx: Pointer to vos global context structure
  pWPSIE:  tSap_WPSIE structure for the station

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_Set_WpsIe
(
    v_PVOID_t pvosGCtx,
    tSap_WPSIE *pWPSIe
);

/*==========================================================================
  FUNCTION   WLANSAP_Update_WpsIe

  DESCRIPTION
    This api function provides for Ap App/HDD to start WPS session.

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
pvosGCtx: Pointer to vos global context structure

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_Update_WpsIe
(
    v_PVOID_t pvosGCtx
);

/*==========================================================================
  FUNCTION    WLANSAP_Stop_Wps

  DESCRIPTION
    This api function provides for Ap App/HDD to stop WPS session.

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
pvosGCtx: Pointer to vos global context structure

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_Stop_Wps
(
    v_PVOID_t pvosGCtx
);

/*==========================================================================
  FUNCTION    WLANSAP_Get_WPS_State

  DESCRIPTION
    This api function provides for Ap App/HDD to get WPS state.

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
pvosGCtx: Pointer to vos global context structure

    OUT
pbWPSState: Pointer to variable to indicate if it is in WPS Registration state

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_Get_WPS_State
(
    v_PVOID_t pvosGCtx,
    v_BOOL_t * pbWPSState
);

/*----------------------------------------------------------------------------
 *  Opaque SAP handle Type Declaration
 * -------------------------------------------------------------------------*/

typedef v_PVOID_t tSapHandle, *ptSapHandle;

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

/*==========================================================================
  FUNCTION    WLANSAP_Open

  DESCRIPTION
    Called at driver initialization (vos_open). SAP will initialize
    all its internal resources and will wait for the call to start to
    register with the other modules.

  DEPENDENCIES

  PARAMETERS

    IN
  pvosGCtx:       pointer to the global vos context; a handle to SAP's
                  control block can be extracted from its context

  RETURN VALUE
    The result code associated with performing the operation

    VOS_STATUS_E_FAULT:  pointer to SAP cb is NULL ; access would cause a page
                         fault
    VOS_STATUS_SUCCESS:  Everything is good :)

  SIDE EFFECTS
============================================================================*/
#ifdef WLAN_FEATURE_MBSSID
v_PVOID_t
#else
VOS_STATUS
#endif
WLANSAP_Open
(
    v_PVOID_t  pvosGCtx
);

/*==========================================================================
  FUNCTION    WLANSAP_Start

  DESCRIPTION
    Called as part of the overall start procedure (vos_start).

  DEPENDENCIES

  PARAMETERS

    IN
    pvosGCtx:       pointer to the global vos context; a handle to SAP's
                    control block can be extracted from its context

  RETURN VALUE
    The result code associated with performing the operation

    VOS_STATUS_E_FAULT:  pointer to SAP cb is NULL ; access would cause a page
                         fault
    VOS_STATUS_SUCCESS:  Everything is good :)

    Other codes can be returned as a result of a BAL failure;

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_Start
(
    v_PVOID_t  pvosGCtx
);

/*==========================================================================
  FUNCTION    WLANSAP_Stop

  DESCRIPTION
    Called by vos_stop to stop operation in SAP, before close.

  DEPENDENCIES

  PARAMETERS

    IN
    pvosGCtx:       pointer to the global vos context; a handle to SAP's
                    control block can be extracted from its context

  RETURN VALUE
    The result code associated with performing the operation

    VOS_STATUS_E_FAULT:  pointer to SAP cb is NULL ; access would cause a page
                         fault
    VOS_STATUS_SUCCESS:  Everything is good :)

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_Stop
(
    v_PVOID_t  pvosGCtx
);

/*==========================================================================
  FUNCTION    WLANSAP_Close

  DESCRIPTION
    Called by vos_close during general driver close procedure. SAP will clean up
    all the internal resources.

  DEPENDENCIES

  PARAMETERS

    IN
    pvosGCtx:       pointer to the global vos context; a handle to SAP's
                    control block can be extracted from its context

  RETURN VALUE
    The result code associated with performing the operation

    VOS_STATUS_E_FAULT:  pointer to SAP cb is NULL ; access would cause a page
                         fault
    VOS_STATUS_SUCCESS:  Everything is good :)

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_Close
(
    v_PVOID_t  pvosGCtx
);

/*==========================================================================
  FUNCTION    (*tpWLAN_SAPEventCB)

  DESCRIPTION
    Implements the callback for ALL asynchronous events.
    Including Events resulting from:
     * Start BSS
     * Stop BSS,...

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
    pSapEvent:  pointer to the union of "Sap Event" structures. This now encodes ALL event types.
        Including Command Complete and Command Status
    pUsrContext   : pUsrContext parameter that was passed to sapStartBss
  RETURN VALUE
    The result code associated with performing the operation

    VOS_STATUS_E_FAULT:  pointer to pSapEvent is NULL
    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
typedef VOS_STATUS (*tpWLAN_SAPEventCB)( tpSap_Event pSapEvent, v_PVOID_t  pUsrContext);



/*==========================================================================
  FUNCTION    WLANSAP_getState

  DESCRIPTION
    This api returns the current SAP state to the caller.

  DEPENDENCIES

  PARAMETERS

    IN
    pContext            : Pointer to Sap Context structure

  RETURN VALUE
    Returns the SAP FSM state.
============================================================================*/

v_U8_t WLANSAP_getState
(
    v_PVOID_t pvosGCtx
);

/*==========================================================================
  FUNCTION    WLANSAP_StartBss

  DESCRIPTION
    This api function provides SAP FSM event eWLAN_SAP_HDD_PHYSICAL_LINK_CREATE for
starting AP BSS

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
pvosGCtx: Pointer to vos global context structure
pConfig: Pointer to configuration structure passed down from HDD(HostApd for Android)
hdd_SapEventCallback: Callback function in HDD called by SAP to inform HDD about SAP results
usrDataForCallback: Parameter that will be passed back in all the SAP callback events.


  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_StartBss
(
    v_PVOID_t pvosGCtx,
    tpWLAN_SAPEventCB pSapEventCallback,
    tsap_Config_t *pConfig,
    v_PVOID_t  pUsrContext
);

#ifdef FEATURE_WLAN_MCC_TO_SCC_SWITCH
/*==========================================================================
  FUNCTION    WLANSAP_CheckCCIntf

  DESCRIPTION Restart SAP if Concurrent Channel interfering

  DEPENDENCIES NA.

  PARAMETERS
  IN
  Ctx: Pointer to vos Context or Sap Context based on MBSSID

  RETURN VALUE Interference channel value

  SIDE EFFECTS
============================================================================*/
v_U16_t WLANSAP_CheckCCIntf(v_PVOID_t Ctx);
#endif
/*==========================================================================
  FUNCTION    WLANSAP_SetMacACL

  DESCRIPTION
  This api function provides SAP to set mac list entry in accept list as well
  as deny list

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
pvosGCtx: Pointer to vos global context structure
pConfig:  Pointer to configuration structure passed down from
          HDD(HostApd for Android)


  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_SetMacACL
(
    v_PVOID_t pvosGCtx,
    tsap_Config_t *pConfig
);

/*==========================================================================
  FUNCTION    WLANSAP_Stop

  DESCRIPTION
    This api function provides SAP FSM event eWLAN_SAP_HDD_PHYSICAL_LINK_DISCONNECT for
stopping BSS

  DEPENDENCIES
    NA.

  PARAMETERS W

    IN
    pvosGCtx: Pointer to vos global context structure

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_StopBss
(
    v_PVOID_t pvosGCtx
);

/*==========================================================================
  FUNCTION    WLANSAP_DisassocSta

  DESCRIPTION
    This api function provides for Ap App/HDD initiated disassociation of station

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
    pvosGCtx            : Pointer to vos global context structure
    pPeerStaMac         : Mac address of the station to disassociate

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_DisassocSta
(
    v_PVOID_t pvosGCtx,
    struct tagCsrDelStaParams *pDelStaParams
);

/*==========================================================================
  FUNCTION    WLANSAP_DeauthSta

  DESCRIPTION
    This api function provides for Ap App/HDD initiated deauthentication of station

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
    pvosGCtx            : Pointer to vos global context structure
    pDelStaParams       : Pointer to parameters of the station to
                          deauthenticate

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_DeauthSta
(
    v_PVOID_t pvosGCtx,
    struct tagCsrDelStaParams *pDelStaParams
);

/*==========================================================================
  FUNCTION    WLANSAP_SetChannelChangeWithCsa

  DESCRIPTION
      This api function does a channel change to the target channel specified
      through an iwpriv. CSA IE is included in the beacons before doing a
      channel change.

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
    pvosGCtx             : Pointer to vos global context structure
    targetChannel        : New target channel to change to.

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_SetChannelChangeWithCsa(v_PVOID_t pvosGCtx, v_U32_t targetChannel);

/*==========================================================================
  FUNCTION    WLANSAP_SetKeySta

  DESCRIPTION
    This api function provides for Ap App/HDD to delete key for a station.

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
pvosGCtx: Pointer to vos global context structure
pSetKeyInfo: tCsrRoamSetKey structure for the station

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_SetKeySta
(
    v_PVOID_t pvosGCtx,
    tCsrRoamSetKey *pSetKeyInfo
);

/*==========================================================================
  FUNCTION    WLANSAP_DelKeySta

  DESCRIPTION
    This api function provides for Ap App/HDD to delete key for a station.

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
pvosGCtx: Pointer to vos global context structure
pSetKeyInfo: tCsrRoamSetKey structure for the station

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_DelKeySta
(
    v_PVOID_t pvosGCtx,
    tCsrRoamRemoveKey *pDelKeyInfo
);


/*==========================================================================
  FUNCTION    WLANSAP_GetAssocStations

  DESCRIPTION
    This api function is used to probe the list of associated stations from various modules of CORE stack

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
pvosGCtx: Pointer to vos global context structure
mod: Module from whom list of associtated stations  is supposed to be probed. If an invalid module is passed
then by default VOS_MODULE_ID_PE will be probed
    IN/OUT
pNoOfAssocStas:- Number of  associated stations that are known to the module specified in mod parameter
pAssocStas: Pointer to list of associated stations that are known to the module specified in mod parameter
NOTE:- The memory for this list will be allocated by the caller of this API

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_GetAssocStations
(
    v_PVOID_t pvosGCtx,
    VOS_MODULE_ID module,
    tpSap_AssocMacAddr pAssocStas
);
/*==========================================================================
  FUNCTION    WLANSAP_RemoveWpsSessionOverlap

  DESCRIPTION
    This api function provides for Ap App/HDD to remove an entry from session session overlap info.

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
    pvosGCtx: Pointer to vos global context structure
    pRemoveMac: pointer to v_MACADDR_t for session MAC address that needs to be removed from wps session

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success
    VOS_STATUS_E_FAULT:  Session is not dectected. The parameter is function not valid.

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_RemoveWpsSessionOverlap

(
    v_PVOID_t pvosGCtx,
    v_MACADDR_t pRemoveMac
);

/*==========================================================================
  FUNCTION    WLANSAP_getWpsSessionOverlap

  DESCRIPTION
    This api function provides for Ap App/HDD to get WPS session overlap info.

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
pvosGCtx: Pointer to vos global context structure
pSessionMac: pointer to v_MACADDR_t for session MAC address
uuide: Pointer to 16 bytes array for session UUID_E

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success
    VOS_STATUS_E_FAULT:  Overlap is dectected. The parameter is function not valid.

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_getWpsSessionOverlap
(
    v_PVOID_t pvosGCtx
);

/*==========================================================================
  FUNCTION    WLANSAP_SetCounterMeasure

  DESCRIPTION
    This api function is used to disassociate all the stations and prevent
    association for any other station.Whenever Authenticator receives 2 mic failures
    within 60 seconds, Authenticator will enable counter measure at SAP Layer.
    Authenticator will start the 60 seconds timer. Core stack will not allow any
    STA to associate till HDD disables counter meassure. Core stack shall kick out all the
    STA which are currently associated and DIASSOC Event will be propogated to HDD for
    each STA to clean up the HDD STA table.Once the 60 seconds timer expires, Authenticator
    will disable the counter meassure at core stack. Now core stack can allow STAs to associate.

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
pvosGCtx: Pointer to vos global context structure
bEnable: If TRUE than all stations will be disassociated and no more will be allowed to associate. If FALSE than CORE
will come out of this state.

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_SetCounterMeasure
(
    v_PVOID_t pvosGCtx,
    v_BOOL_t bEnable
);

/*==========================================================================
  FUNCTION    WLANSap_getstationIE_information

  DESCRIPTION
    This api function provides for Ap App/HDD to retrive the WPA and RSNIE of a station.

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
        pvosGCtx: Pointer to vos global context structure
        pLen : length of WPARSN elment IE where it would be copied
        pBuf : buf to copy the WPARSNIe

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSap_getstationIE_information
(
    v_PVOID_t pvosGCtx,
    v_U32_t   *pLen,
    v_U8_t    *pBuf
);

/*==========================================================================
  FUNCTION    WLANSAP_ClearACL

  DESCRIPTION
    This api function removes all the entries in both accept and deny lists.

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
        pvosGCtx: Pointer to vos global context structure

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_ClearACL
(
    v_PVOID_t pvosGCtx
);

/*==========================================================================
  FUNCTION    WLANSAP_GetACLAcceptList

  DESCRIPTION
    This api function to get ACL accept list.

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
        pvosGCtx: Pointer to vos global context structure
        pAcceptList: ACL Accept list entries
        nAcceptList: Number of entries in ACL Accept list

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_GetACLAcceptList
(
    v_PVOID_t pvosGCtx,
    v_MACADDR_t *pAcceptList,
    v_U8_t *nAcceptList
);

/*==========================================================================
  FUNCTION    WLANSAP_GetACLDenyList

  DESCRIPTION
    This api function to get ACL Deny list.

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
        pvosGCtx: Pointer to vos global context structure
        pAcceptList: ACL Deny list entries
        nAcceptList: Number of entries in ACL Deny list

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_GetACLDenyList
(
   v_PVOID_t pCtx,
   v_MACADDR_t *pDenyList,
   v_U8_t *nDenyList
);

/*==========================================================================
  FUNCTION    WLANSAP_SetMode

  DESCRIPTION
    This api is used to set mode for ACL

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
        pvosGCtx: Pointer to vos global context structure

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_SetMode
(
    v_PVOID_t pvosGCtx,
    v_U32_t mode
);

/*==========================================================================
  FUNCTION    WLANSAP_GetACLMode

  DESCRIPTION
    This api is used to get mode for ACL

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
        pvosGCtx: Pointer to vos global context structure
        mode: Current Mode of the ACL

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_GetACLMode
(
    v_PVOID_t pvosGCtx,
    eSapMacAddrACL *mode
);

/*==========================================================================
  FUNCTION    WLANSAP_ModifyACL

  DESCRIPTION
    This api function provides for Ap App/HDD to add/remove mac addresses from black/white lists (ACLs).

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
        pvosGCtx        : Pointer to vos global context structure
        pPeerStaMac     : MAC address to be added or removed
        listType        : add/remove to be done on black or white list
        cmd             : Are we doing to add or delete a mac addr from an ACL.
  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_ModifyACL
(
    v_PVOID_t pvosGCtx,
    v_U8_t *pPeerStaMac,
    eSapACLType listType,
    eSapACLCmdType cmd
);

/*==========================================================================
  FUNCTION    WLANSAP_Set_WPARSNIes

  DESCRIPTION
    This api function provides for Ap App/HDD to set AP WPA and RSN IE in its beacon and probe response.

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
        pvosGCtx: Pointer to vos global context structure
        pWPARSNIEs: buffer to the WPA/RSN IEs
        WPARSNIEsLen: length of WPA/RSN IEs

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS WLANSAP_Set_WPARSNIes
(
    v_PVOID_t pvosGCtx,
    v_U8_t *pWPARSNIEs,
    v_U32_t WPARSNIEsLen
);

/*==========================================================================
  FUNCTION    WLANSAP_GetStatistics

  DESCRIPTION
    This api function provides for Ap App/HDD to get TL statistics for all stations of Soft AP.

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
        pvosGCtx: Pointer to vos global context structure
        bReset: If set TL statistics will be cleared after reading
    OUT
        statBuf: Buffer to get the statistics

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS WLANSAP_GetStatistics
(
    v_PVOID_t pvosGCtx,
    tSap_SoftapStats *statBuf,
    v_BOOL_t bReset
);

/*==========================================================================

  FUNCTION    WLANSAP_SendAction

  DESCRIPTION
    This api function provides to send action frame sent by upper layer.

  DEPENDENCIES
    NA.

  PARAMETERS

  IN
    pvosGCtx: Pointer to vos global context structure
    pBuf: Pointer of the action frame to be transmitted
    len: Length of the action frame

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS WLANSAP_SendAction
(
    v_PVOID_t pvosGCtx,
    const tANI_U8 *pBuf,
    tANI_U32 len,
    tANI_U16 wait
);

/*==========================================================================

  FUNCTION    WLANSAP_RemainOnChannel

  DESCRIPTION
    This api function provides to set Remain On channel on specified channel
    for specified duration.

  DEPENDENCIES
    NA.

  PARAMETERS

  IN
    pvosGCtx: Pointer to vos global context structure
    channel: Channel on which driver has to listen
    duration: Duration for which driver has to listen on specified channel
    callback: Callback function to be called once Listen is done.
    pContext: Context needs to be called in callback function.

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS WLANSAP_RemainOnChannel
(
    v_PVOID_t pvosGCtx,
    tANI_U8 channel,
    tANI_U32 duration,
    remainOnChanCallback callback,
    void *pContext
);

/*==========================================================================

  FUNCTION    WLANSAP_CancelRemainOnChannel

  DESCRIPTION
    This api cancel previous remain on channel request.

  DEPENDENCIES
    NA.

  PARAMETERS

  IN
    pvosGCtx: Pointer to vos global context structure

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS WLANSAP_CancelRemainOnChannel
(
    v_PVOID_t pvosGCtx
);


/*==========================================================================

  FUNCTION    WLANSAP_RegisterMgmtFrame

  DESCRIPTION
    HDD use this API to register specified type of frame with CORE stack.
    On receiving such kind of frame CORE stack should pass this frame to HDD

  DEPENDENCIES
    NA.

  PARAMETERS

  IN
    pvosGCtx: Pointer to vos global context structure
    frameType: frameType that needs to be registered with PE.
    matchData: Data pointer which should be matched after frame type is matched.
    matchLen: Length of the matchData

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS WLANSAP_RegisterMgmtFrame
(
    v_PVOID_t pvosGCtx,
    tANI_U16 frameType,
    tANI_U8* matchData,
    tANI_U16 matchLen
);

/*==========================================================================

  FUNCTION    WLANSAP_DeRegisterMgmtFrame

  DESCRIPTION
   This API is used to deregister previously registered frame.

  DEPENDENCIES
    NA.

  PARAMETERS

  IN
    pvosGCtx: Pointer to vos global context structure
    frameType: frameType that needs to be De-registered with PE.
    matchData: Data pointer which should be matched after frame type is matched.
    matchLen: Length of the matchData

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS WLANSAP_DeRegisterMgmtFrame
(
    v_PVOID_t pvosGCtx,
    tANI_U16 frameType,
    tANI_U8* matchData,
    tANI_U16 matchLen
);

/*==========================================================================

 FUNCTION    WLANSAP_ChannelChangeRequest
 DESCRIPTION
  This API is used to send an Indication to SME/PE to change the
  current operating channel to a different target channel.

  The Channel change will be issued by SAP under the following
  scenarios.
  1. A radar indication is received  during SAP CAC WAIT STATE and
     channel change is required.
  2. A radar indication is received during SAP STARTED STATE and
     channel change is required.

 DEPENDENCIES
  NA.

PARAMETERS

IN
  pvosGCtx: Pointer to vos global context structure
  TargetChannel: New target channel for channel change.

RETURN VALUE
  The VOS_STATUS code associated with performing the operation

VOS_STATUS_SUCCESS:  Success

SIDE EFFECTS
============================================================================*/
VOS_STATUS WLANSAP_ChannelChangeRequest(v_PVOID_t pvosGCtx, tANI_U8 tArgetChannel);

/*==========================================================================

 FUNCTION    WLANSAP_StartBeaconReq
 DESCRIPTION
  This API is used to send an Indication to SME/PE to start
  beaconing on the current operating channel.

  Brief:When SAP is started on DFS channel and when ADD BSS RESP is received
  LIM temporarily holds off Beaconing for SAP to do CAC WAIT. When
  CAC WAIT is done SAP resumes the Beacon Tx by sending a start beacon
  request to LIM.

 DEPENDENCIES
  NA.

PARAMETERS

IN
  pvosGCtx: Pointer to vos global context structure

RETURN VALUE
  The VOS_STATUS code associated with performing the operation

VOS_STATUS_SUCCESS:  Success

SIDE EFFECTS
============================================================================*/
VOS_STATUS WLANSAP_StartBeaconReq(v_PVOID_t pSapCtx);

/*==========================================================================
  FUNCTION    WLANSAP_DfsSendCSAIeRequest

  DESCRIPTION
   This API is used to send channel switch announcement request to PE
  DEPENDENCIES
   NA.

  PARAMETERS
  IN
  sapContext: Pointer to vos global context structure

  RETURN VALUE
  The VOS_STATUS code associated with performing the operation

  VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_DfsSendCSAIeRequest(v_PVOID_t pSapCtx);

/*==========================================================================
  FUNCTION    WLANSAP_Get_Dfs_Ignore_CAC

  DESCRIPTION
   This API is used to get ignore_cac flag.

  DEPENDENCIES
   NA.

  PARAMETERS
  IN
  pvosGCtx: Pointer to vos global context structure

  PARAMETERS
  OUT
  pIgnore_cac: pointer to variable

  RETURN VALUE
  The VOS_STATUS code associated with performing the operation

  VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/

VOS_STATUS
WLANSAP_Get_Dfs_Ignore_CAC(tHalHandle hHal, v_U8_t *pIgnore_cac);


/*==========================================================================
  FUNCTION    WLANSAP_Set_Dfs_Ignore_CAC

  DESCRIPTION
   This API is used to set ignore_cac flag, used for ignoring the CAC operation for DFS channel.
   If the flag set to 1 or TRUE then it will avoid CAC.

  DEPENDENCIES
   NA.

  PARAMETERS
  IN
  pvosGCtx: Pointer to vos global context structure

  PARAMETERS
  IN
  ignore_cac: value to be set

  RETURN VALUE
  The VOS_STATUS code associated with performing the operation

  VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/

VOS_STATUS
WLANSAP_Set_Dfs_Ignore_CAC(tHalHandle hHal, v_U8_t ignore_cac);

/*==========================================================================
  FUNCTION    WLANSAP_set_Dfs_Restrict_JapanW53

  DESCRIPTION
   This API is used to enable or disable Japan W53 Band

  DEPENDENCIES
   NA.

  PARAMETERS
  IN
  hHal : HAL pointer
  disable_Dfs_JapanW3 :Indicates if Japan W53 is disabled when set to 1
                       Indicates if Japan W53 is enabled when set to 0

  RETURN VALUE
  The VOS_STATUS code associated with performing the operation

  VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_set_Dfs_Restrict_JapanW53(tHalHandle hHal, v_U8_t disable_Dfs_JapanW3);

#ifdef FEATURE_AP_MCC_CH_AVOIDANCE
/**
 * wlan_sap_set_channel_avoidance() - sets sap mcc channel avoidance ini param
 * @hal:                        hal handle
 * @sap_channel_avoidance:      ini parameter value
 *
 * sets sap mcc channel avoidance ini param, to be called in sap_start
 *
 * Return: success of failure of operation
 */
VOS_STATUS
wlan_sap_set_channel_avoidance(tHalHandle hal, bool sap_channel_avoidance);
#endif /* FEATURE_AP_MCC_CH_AVOIDANCE */

/*==========================================================================
  FUNCTION    WLANSAP_set_Dfs_Preferred_Channel_location

  DESCRIPTION
   This API is used to set sap preferred channels location
   to resetrict the DFS random channel selection algorithm
   either Indoor/Outdoor channels only.

  DEPENDENCIES
   NA.

  PARAMETERS
  IN
  hHal : HAL pointer
  dfs_Preferred_Channels_location :
                       0 - Indicates No preferred channel location restrictions
                       1 - Indicates SAP Indoor Channels operation only.
                       2 - Indicates SAP Outdoor Channels operation only.

  RETURN VALUE
  The VOS_STATUS code associated with performing the operation

  VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_set_Dfs_Preferred_Channel_location(tHalHandle hHal,
                                   v_U8_t dfs_Preferred_Channels_location);

/*==========================================================================
  FUNCTION   WLANSAP_Set_Dfs_Target_Chnl

  DESCRIPTION
   This API is used to set next target chnl as provided channel.
   you can provide any valid channel to this API.

  DEPENDENCIES
   NA.

  PARAMETERS
  IN
  hHal: Pointer to HAL

  PARAMETERS
  IN
  target_channel: target channel number

  RETURN VALUE
  The VOS_STATUS code associated with performing the operation

  VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/

VOS_STATUS
WLANSAP_Set_Dfs_Target_Chnl(tHalHandle hHal,
                            v_U8_t target_channel);



/*==========================================================================
  FUNCTION   wlan_sap_get_vht_ch_width

  DESCRIPTION Returns the SAP VHT channel width.

  DEPENDENCIES NA.

  PARAMETERS
  IN
  ctx: Pointer to vos Context or Sap Context based on MBSSID

  RETURN VALUE VHT channnel width

  SIDE EFFECTS
============================================================================*/
v_U32_t wlan_sap_get_vht_ch_width(v_PVOID_t ctx);

/*==========================================================================
  FUNCTION   wlan_sap_set_vht_ch_width

  DESCRIPTION Sets the SAP VHT channel width.

  DEPENDENCIES NA.

  PARAMETERS
  IN
  ctx: Pointer to vos Context or Sap Context based on MBSSID
  vht_channel_width - VHT channel width

  RETURN VALUE NONE

  SIDE EFFECTS
============================================================================*/
void wlan_sap_set_vht_ch_width(v_PVOID_t ctx, v_U32_t vht_channel_width);

/*==========================================================================
  FUNCTION    WLANSAP_UpdateSapConfigAddIE

  DESCRIPTION
   This API is used to set sap config parameter.

  DEPENDENCIES
   NA.

  PARAMETERS
  IN OUT
  pConfig:  Pointer to sap config

  PARAMETERS
  IN
  additionIEBuffer - buffer containing addition IE from hostapd

  PARAMETERS
  IN
  additionIELength - length of buffer

  PARAMETERS
  IN
  updateType - Type of buffer

  RETURN VALUE
  The VOS_STATUS code associated with performing the operation

  VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/

VOS_STATUS WLANSAP_UpdateSapConfigAddIE(tsap_Config_t *pConfig,
                         const tANI_U8 *pAdditionIEBuffer,
                         tANI_U16 additionIELength,
                         eUpdateIEsType updateType);

/*==========================================================================
  FUNCTION    WLANSAP_ResetSapConfigAddIE

  DESCRIPTION
   This API is used to reset and clear the buffer in sap config.

  DEPENDENCIES
   NA.

  PARAMETERS
  IN OUT
  pConfig:  Pointer to sap config
  PARAMETERS
  IN
  updateType:  type buffer
  RETURN VALUE
  The VOS_STATUS code associated with performing the operation

  VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/

VOS_STATUS
WLANSAP_ResetSapConfigAddIE(tsap_Config_t *pConfig,
                            eUpdateIEsType updateType);

/*==========================================================================
FUNCTION  WLANSAP_extend_to_acs_range

DESCRIPTION Function extends give channel range to consider ACS chan bonding

DEPENDENCIES PARAMETERS

IN /OUT
*startChannelNum : ACS extend start ch
*endChannelNum   : ACS extended End ch
*bandStartChannel: Band start ch
*bandEndChannel  : Band end ch

RETURN VALUE NONE

SIDE EFFECTS
============================================================================*/
v_VOID_t WLANSAP_extend_to_acs_range(v_U8_t *startChannelNum,
                                  v_U8_t *endChannelNum,
                                  v_U8_t *bandStartChannel,
                                  v_U8_t *bandEndChannel);

/*==========================================================================
  FUNCTION    WLANSAP_Get_DfsNol

  DESCRIPTION
  This API is used to dump the dfs nol
  DEPENDENCIES
  NA.

  PARAMETERS
  IN
  sapContext: Pointer to vos global context structure

  RETURN VALUE
  The VOS_STATUS code associated with performing the operation

  VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_Get_DfsNol(v_PVOID_t pSapCtx);

/*==========================================================================
  FUNCTION    WLANSAP_Set_DfsNol

  DESCRIPTION
  This API is used to set the dfs nol
  DEPENDENCIES
  NA.

  PARAMETERS
  IN
  sapContext: Pointer to vos global context structure
  conf: set type

  RETURN VALUE
  The VOS_STATUS code associated with performing the operation

  VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_Set_DfsNol(v_PVOID_t pSapCtx, eSapDfsNolType conf);

/*==========================================================================
  FUNCTION    WLANSAP_PopulateDelStaParams

  DESCRIPTION
  This API is used to populate del station parameters
  DEPENDENCIES
  NA.

  PARAMETERS
  IN
  mac:           pointer to peer mac address.
  reason_code:   Reason code for the disassoc/deauth.
  subtype:       subtype points to either disassoc/deauth frame.
  pDelStaParams: address where parameters to be populated.

  RETURN VALUE NONE

  SIDE EFFECTS
============================================================================*/

void WLANSAP_PopulateDelStaParams(const v_U8_t *mac,
                                  v_U16_t reason_code,
                                  v_U8_t subtype,
                                  struct tagCsrDelStaParams *pDelStaParams);

/*==========================================================================
  FUNCTION    WLANSAP_ACS_CHSelect

  DESCRIPTION
    This api function provides ACS selection for BSS

  DEPENDENCIES
    NA.

  PARAMETERS

    IN
      pvosGCtx: Pointer to vos global context structure
      pConfig: Pointer to configuration structure passed down from HDD
      pACSEventCallback: Callback function in HDD called by SAP to inform
                         HDD about channel section result
      usrDataForCallback: Parameter that will be passed back in all the
                          SAP callback events.

  RETURN VALUE
    The VOS_STATUS code associated with performing the operation

    VOS_STATUS_SUCCESS:  Success

  SIDE EFFECTS
============================================================================*/
VOS_STATUS
WLANSAP_ACS_CHSelect(v_PVOID_t pvosGCtx,
                     tpWLAN_SAPEventCB pACSEventCallback,
                     tsap_Config_t *pConfig,
                     v_PVOID_t  pUsrContext);

eCsrPhyMode
wlansap_get_phymode(v_PVOID_t pctx);

VOS_STATUS wlansap_set_tx_leakage_threshold(tHalHandle hal,
			uint16 tx_leakage_threshold);

VOS_STATUS wlansap_set_invalid_session(v_PVOID_t pctx);

#ifdef __cplusplus
 }
#endif


#endif /* #ifndef WLAN_QCT_WLANSAP_H */
