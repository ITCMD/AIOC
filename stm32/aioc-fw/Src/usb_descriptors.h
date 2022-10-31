#ifndef USB_DESCRIPTORS_H_
#define USB_DESCRIPTORS_H_

/* Interfaces */
enum USB_DESCRIPTORS_ITF {
  ITF_NUM_CDC_0 = 0,
  ITF_NUM_CDC_0_DATA,
  ITF_NUM_AUDIO_CONTROL,
  ITF_NUM_AUDIO_STREAMING_OUT,
  ITF_NUM_AUDIO_STREAMING_IN,
  ITF_NUM_TOTAL
};

/* Endpoints */
#define EPNUM_AUDIO_IN      0x81
#define EPNUM_AUDIO_OUT     0x02
#define EPNUM_AUDIO_FB      0x82
#define EPNUM_CDC_0_OUT     0x03
#define EPNUM_CDC_0_IN      0x83
#define EPNUM_CDC_0_NOTIF   0x84

/* Custom Audio Descriptor.
 * Courtesy of https://github.com/hathach/tinyusb/issues/1249#issuecomment-1148727765 */
#define AUDIO_CTRL_ID_SPK_INPUT_STREAM 0x01
#define AUDIO_CTRL_ID_SPK_FUNIT 0x02
#define AUDIO_CTRL_ID_SPK_OUTPUT 0x03
#define AUDIO_CTRL_ID_MIC_INPUT 0x04
#define AUDIO_CTRL_ID_MIC_FUNIT 0x05
#define AUDIO_CTRL_ID_MIC_OUTPUT_STREAM 0x06
#define AUDIO_CTRL_ID_CLOCK 0x41
#define AUDIO_CTRL_ID_CLOCKSEL 0x40

#define AUDIO_NUM_INTERFACES 0x03
#define AUDIO_NUM_INCHANNELS 0x01
#define AUDIO_NUM_OUTCHANNELS 0x01

#define TUD_AUDIO_CTRL_TOTAL_LEN ( \
    TUD_AUDIO_DESC_CLK_SRC_LEN + \
    TUD_AUDIO_DESC_INPUT_TERM_LEN + \
    TUD_AUDIO_DESC_OUTPUT_TERM_LEN + \
    TUD_AUDIO_DESC_INPUT_TERM_LEN + \
    TUD_AUDIO_DESC_OUTPUT_TERM_LEN)

#define TUD_AUDIO_IO_DESC_LEN ( \
    TUD_AUDIO_DESC_IAD_LEN + \
    TUD_AUDIO_DESC_STD_AC_LEN + \
    TUD_AUDIO_DESC_CS_AC_LEN + \
    TUD_AUDIO_CTRL_TOTAL_LEN + \
    /* Speaker Interface */ \
    TUD_AUDIO_DESC_STD_AS_INT_LEN + \
    TUD_AUDIO_DESC_STD_AS_INT_LEN + \
    TUD_AUDIO_DESC_CS_AS_INT_LEN + \
    TUD_AUDIO_DESC_TYPE_I_FORMAT_LEN + \
    TUD_AUDIO_DESC_STD_AS_ISO_EP_LEN + \
    TUD_AUDIO_DESC_CS_AS_ISO_EP_LEN + \
    TUD_AUDIO_DESC_STD_AS_ISO_EP_LEN + \
    /* Microphone Interface */ \
    TUD_AUDIO_DESC_STD_AS_INT_LEN + \
    TUD_AUDIO_DESC_STD_AS_INT_LEN + \
    TUD_AUDIO_DESC_CS_AS_INT_LEN + \
    TUD_AUDIO_DESC_TYPE_I_FORMAT_LEN + \
    TUD_AUDIO_DESC_STD_AS_ISO_EP_LEN + \
    TUD_AUDIO_DESC_CS_AS_ISO_EP_LEN)

#define TUD_AUDIO_IO_DESCRIPTOR(_itfnum, _stridx, _nBytesPerSample, _nBitsUsedPerSample, _epin, _epinsize, _epout, _epoutsize, _epfb) \
    /* Standard Interface Association Descriptor (IAD) */ \
    TUD_AUDIO_DESC_IAD(_itfnum, AUDIO_NUM_INTERFACES, /*_stridx*/ 0x00), \
    /* Audio Control Interface */ \
    /* Standard AC Interface Descriptor(4.7.1) */ \
    TUD_AUDIO_DESC_STD_AC(/*_itfnum*/ _itfnum, /*_nEPs*/ 0x00, /*_stridx*/ _stridx), \
    /* Class-Specific AC Interface Header Descriptor(4.7.2) */ \
    TUD_AUDIO_DESC_CS_AC(/*_bcdADC*/ 0x0200, AUDIO_FUNC_CONVERTER, TUD_AUDIO_CTRL_TOTAL_LEN, /*_ctrl*/ AUDIO_CS_AS_INTERFACE_CTRL_LATENCY_POS), \
    /* Clock Source Descriptor(4.7.2.1) */ \
    TUD_AUDIO_DESC_CLK_SRC(AUDIO_CTRL_ID_CLOCK, AUDIO_CLOCK_SOURCE_ATT_INT_FIX_CLK, (AUDIO_CTRL_R << AUDIO_CLOCK_SOURCE_CTRL_CLK_FRQ_POS), /*_assocTerm*/ 0x01, /*_stridx*/ 0x00), \
    /* Speaker Terminals */ \
    TUD_AUDIO_DESC_INPUT_TERM(/*_termid*/ AUDIO_CTRL_ID_SPK_INPUT_STREAM, /*_termtype*/ AUDIO_TERM_TYPE_USB_STREAMING, /*_assocTerm*/ AUDIO_CTRL_ID_MIC_OUTPUT_STREAM, /*_clkid*/ AUDIO_CTRL_ID_CLOCK, /*_nchannelslogical*/ AUDIO_NUM_OUTCHANNELS, /*_channelcfg*/ AUDIO_CHANNEL_CONFIG_NON_PREDEFINED, /*_idxchannelnames*/ 0x00, /*_ctrl*/ AUDIO_CTRL_R << AUDIO_IN_TERM_CTRL_CONNECTOR_POS, /*_stridx*/ 0x00), \
    TUD_AUDIO_DESC_OUTPUT_TERM(AUDIO_CTRL_ID_SPK_OUTPUT, AUDIO_TERM_TYPE_OUT_GENERIC_SPEAKER, AUDIO_CTRL_ID_SPK_INPUT_STREAM, AUDIO_CTRL_ID_SPK_INPUT_STREAM, AUDIO_CTRL_ID_CLOCK, /*_ctrl*/ 0x0000, /*_stridx*/ 0x00), \
    /* Microphone Terminals */ \
    TUD_AUDIO_DESC_INPUT_TERM(AUDIO_CTRL_ID_MIC_INPUT, AUDIO_TERM_TYPE_IN_GENERIC_MIC, AUDIO_CTRL_ID_MIC_OUTPUT_STREAM, AUDIO_CTRL_ID_CLOCK, AUDIO_NUM_INCHANNELS, AUDIO_CHANNEL_CONFIG_NON_PREDEFINED, /*_idxchannelnames*/ 0x00, /*_ctrl*/ AUDIO_CTRL_R << AUDIO_IN_TERM_CTRL_CONNECTOR_POS, /*_stridx*/ 0x00), \
    TUD_AUDIO_DESC_OUTPUT_TERM(AUDIO_CTRL_ID_MIC_OUTPUT_STREAM, AUDIO_TERM_TYPE_USB_STREAMING, AUDIO_CTRL_ID_MIC_INPUT, AUDIO_CTRL_ID_MIC_INPUT, AUDIO_CTRL_ID_CLOCK, /*_ctrl*/ 0x0000, /*_stridx*/ 0x00), \
    /* Speaker Interface */ \
    /* Interface 1, Alternate 0 - default alternate setting with 0 bandwidth */ \
    TUD_AUDIO_DESC_STD_AS_INT(/*_itfnum*/ (uint8_t)((_itfnum) + 1), /*_altset*/ 0x00, /*_nEPs*/ 0x00, /*_stridx*/ 0x00), \
    /* Interface 1, Alternate 1 - alternate interface for data streaming */ \
    TUD_AUDIO_DESC_STD_AS_INT(/*_itfnum*/ (uint8_t)((_itfnum) + 1), /*_altset*/ 0x01, /*_nEPs*/ 0x02, /*_stridx*/ 0x00), \
    /* Class-Specific AS Interface Descriptor(4.9.2) */ \
    TUD_AUDIO_DESC_CS_AS_INT(AUDIO_CTRL_ID_SPK_INPUT_STREAM, AUDIO_CTRL_NONE, AUDIO_FORMAT_TYPE_I, AUDIO_DATA_FORMAT_TYPE_I_PCM, AUDIO_NUM_OUTCHANNELS, AUDIO_CHANNEL_CONFIG_NON_PREDEFINED, /*_stridx*/ 0x00), \
    /* Type I Format Type Descriptor(2.3.1.6 - Audio Formats) */ \
    TUD_AUDIO_DESC_TYPE_I_FORMAT(_nBytesPerSample, _nBitsUsedPerSample), \
    /* Standard AS Isochronous Audio Data Endpoint Descriptor(4.10.1.1) */ \
    TUD_AUDIO_DESC_STD_AS_ISO_EP(_epout, (TUSB_XFER_ISOCHRONOUS | TUSB_ISO_EP_ATT_ASYNCHRONOUS | TUSB_ISO_EP_ATT_DATA), _epoutsize, TUD_OPT_HIGH_SPEED ? 0x04 : 0x01), \
    /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor(4.10.1.2) */ \
    TUD_AUDIO_DESC_CS_AS_ISO_EP(AUDIO_CS_AS_ISO_DATA_EP_ATT_NON_MAX_PACKETS_OK, AUDIO_CTRL_NONE, AUDIO_CS_AS_ISO_DATA_EP_LOCK_DELAY_UNIT_UNDEFINED, 0x0000), \
    /* Standard AS Isochronous Feedback Endpoint Descriptor(4.10.2.1) */ \
    TUD_AUDIO_DESC_STD_AS_ISO_FB_EP(_epfb, 1), \
    /* Microphone Interface */ \
    /* Standard AS Interface Descriptor(4.9.1) */ \
    /* Interface 1, Alternate 0 - default alternate setting with 0 bandwidth */ \
    TUD_AUDIO_DESC_STD_AS_INT((uint8_t)((_itfnum)+2), /*_altset*/ 0x00, /*_nEPs*/ 0x00, /*_stridx*/ 0x00), \
    /* Standard AS Interface Descriptor(4.9.1) */ \
    /* Interface 1, Alternate 1 - alternate interface for data streaming */ \
    TUD_AUDIO_DESC_STD_AS_INT(/*_itfnum*/ (uint8_t)((_itfnum)+2), /*_altset*/ 0x01, /*_nEPs*/ 0x01, /*_stridx*/ 0x00), \
    /* Class-Specific AS Interface Descriptor(4.9.2) */ \
    TUD_AUDIO_DESC_CS_AS_INT(AUDIO_CTRL_ID_MIC_OUTPUT_STREAM, AUDIO_CTRL_NONE, AUDIO_FORMAT_TYPE_I, AUDIO_DATA_FORMAT_TYPE_I_PCM, AUDIO_NUM_INCHANNELS, AUDIO_CHANNEL_CONFIG_NON_PREDEFINED, /*_stridx*/ 0x00), \
    /* Type I Format Type Descriptor(2.3.1.6 - Audio Formats) */ \
    TUD_AUDIO_DESC_TYPE_I_FORMAT(_nBytesPerSample, _nBitsUsedPerSample), \
    /* Standard AS Isochronous Audio Data Endpoint Descriptor(4.10.1.1) */ \
    TUD_AUDIO_DESC_STD_AS_ISO_EP(_epin, (TUSB_XFER_ISOCHRONOUS | TUSB_ISO_EP_ATT_ASYNCHRONOUS | TUSB_ISO_EP_ATT_DATA), _epinsize, TUD_OPT_HIGH_SPEED ? 0x04 : 0x01), \
    /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor(4.10.1.2) */ \
    TUD_AUDIO_DESC_CS_AS_ISO_EP(AUDIO_CS_AS_ISO_DATA_EP_ATT_NON_MAX_PACKETS_OK, AUDIO_CTRL_NONE, AUDIO_CS_AS_ISO_DATA_EP_LOCK_DELAY_UNIT_UNDEFINED, 0x0000)


#endif /* USB_DESCRIPTORS_H_ */
