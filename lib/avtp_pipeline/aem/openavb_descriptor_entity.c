/*
 ******************************************************************
 * COPYRIGHT � Symphony Teleca
 *----------------------------------------------------------------*
 * MODULE : AEM - AVDECC Entity Descriptor
 *
 * PROGRAMMER : Ken Carlino (Triple Play Integration)
 * DATE :       21-Nov-2013
 * VERSION :    1.0
 *
 *----------------------------------------------------------------*
 *
 * MODULE SUMMARY : Implements the AVDECC Entity Descriptor IEEE Std 1722.1-2013 clause 7.2.1 
 *
 *----------------------------------------------------------------*
 *
 * MODIFICATION RECORDS
 *
 ******************************************************************
 */
#include "openavb_platform.h"

#include <stdlib.h>

#define	AVB_LOG_COMPONENT	"AEM"
#include "openavb_log.h"

#include "openavb_rawsock.h"
#include "openavb_aem.h"
#include "openavb_descriptor_entity.h"


////////////////////////////////
// Private (internal) functions
////////////////////////////////
openavbRC openavbAemDescriptorEntityToBuf(void *pVoidDescriptor, U16 bufLength, U8 *pBuf, U16 *descriptorSize)
{
	AVB_TRACE_ENTRY(AVB_TRACE_AEM);

	openavb_aem_descriptor_entity_t *pDescriptor = pVoidDescriptor;

	if (!pDescriptor || !pBuf || !descriptorSize) {
		AVB_RC_LOG_TRACE_RET(AVB_RC(OPENAVB_AVDECC_FAILURE | OPENAVB_RC_INVALID_ARGUMENT), AVB_TRACE_AEM);
	}

	if (bufLength < OPENAVB_DESCRIPTOR_ENTITY_BASE_LENGTH) {
		AVB_RC_LOG_TRACE_RET(AVB_RC(OPENAVB_AVDECC_FAILURE | OPENAVBAVDECC_RC_BUFFER_TOO_SMALL), AVB_TRACE_AEM);
	}

	*descriptorSize = 0;

	openavb_aem_descriptor_entity_t *pSrc = pDescriptor;
	U8 *pDst = pBuf;

	OCT_D2BHTONS(pDst, pSrc->descriptor_type);
	OCT_D2BHTONS(pDst, pSrc->descriptor_index);
	OCT_D2BMEMCP(pDst, pSrc->entity_id);
	OCT_D2BMEMCP(pDst, pSrc->entity_model_id);
	OCT_D2BHTONL(pDst, pSrc->entity_capabilities);
	OCT_D2BHTONS(pDst, pSrc->talker_stream_sources);
	OCT_D2BHTONS(pDst, pSrc->talker_capabilities);
	OCT_D2BHTONS(pDst, pSrc->listener_stream_sinks);
	OCT_D2BHTONS(pDst, pSrc->listener_capabilities);
	OCT_D2BHTONL(pDst, pSrc->controller_capabilities);
	OCT_D2BHTONL(pDst, pSrc->available_index);
	OCT_D2BMEMCP(pDst, pSrc->association_id);
	OCT_D2BMEMCP(pDst, pSrc->entity_name);
	BIT_D2BHTONS(pDst, pSrc->vendor_name_string.offset, 3, 0);
	BIT_D2BHTONS(pDst, pSrc->vendor_name_string.index, 0, 2);
	BIT_D2BHTONS(pDst, pSrc->model_name_string.offset, 3, 0);
	BIT_D2BHTONS(pDst, pSrc->model_name_string.index, 0, 2);
	OCT_D2BMEMCP(pDst, pSrc->firmware_version);
	OCT_D2BMEMCP(pDst, pSrc->group_name);
	OCT_D2BMEMCP(pDst, pSrc->serial_number);
	OCT_D2BHTONS(pDst, pSrc->configurations_count);
	OCT_D2BHTONS(pDst, pSrc->current_configuration);

	*descriptorSize = pDst - pBuf;

	AVB_RC_TRACE_RET(OPENAVB_AVDECC_SUCCESS, AVB_TRACE_AEM);
}

openavbRC openavbAemDescriptorEntityFromBuf(void *pVoidDescriptor, U16 bufLength, U8 *pBuf)
{
	AVB_TRACE_ENTRY(AVB_TRACE_AEM);

	openavb_aem_descriptor_entity_t *pDescriptor = pVoidDescriptor;

	if (!pDescriptor || !pBuf) {
		AVB_RC_LOG_TRACE_RET(AVB_RC(OPENAVB_AVDECC_FAILURE | OPENAVB_RC_INVALID_ARGUMENT), AVB_TRACE_AEM);
	}

	if (bufLength < OPENAVB_DESCRIPTOR_ENTITY_BASE_LENGTH) {
		AVB_RC_LOG_TRACE_RET(AVB_RC(OPENAVB_AVDECC_FAILURE | OPENAVBAVDECC_RC_BUFFER_TOO_SMALL), AVB_TRACE_AEM);
	}

	U8 *pSrc = pBuf;
	openavb_aem_descriptor_entity_t *pDst = pDescriptor;

	OCT_B2DNTOHS(pDst->descriptor_type, pSrc);
	OCT_B2DNTOHS(pDst->descriptor_index, pSrc);
	OCT_B2DMEMCP(pDst->entity_id, pSrc);
	OCT_B2DMEMCP(pDst->entity_model_id, pSrc);
	OCT_B2DNTOHL(pDst->entity_capabilities, pSrc);
	OCT_B2DNTOHS(pDst->talker_stream_sources, pSrc);
	OCT_B2DNTOHS(pDst->talker_capabilities, pSrc);
	OCT_B2DNTOHS(pDst->listener_stream_sinks, pSrc);
	OCT_B2DNTOHS(pDst->listener_capabilities, pSrc);
	OCT_B2DNTOHL(pDst->controller_capabilities, pSrc);
	OCT_B2DNTOHL(pDst->available_index, pSrc);
	OCT_B2DMEMCP(pDst->association_id, pSrc);
	OCT_B2DMEMCP(pDst->entity_name, pSrc);
	BIT_B2DNTOHS(pDst->vendor_name_string.offset, pSrc, 0xfff8, 3, 0);
	BIT_B2DNTOHS(pDst->vendor_name_string.index, pSrc, 0x0007, 0, 2);
	BIT_B2DNTOHS(pDst->model_name_string.offset, pSrc, 0xfff8, 3, 0);
	BIT_B2DNTOHS(pDst->model_name_string.index, pSrc, 0x0007, 0, 2);
	OCT_B2DMEMCP(pDst->firmware_version, pSrc);
	OCT_B2DMEMCP(pDst->group_name, pSrc);
	OCT_B2DMEMCP(pDst->serial_number, pSrc);
	OCT_B2DNTOHS(pDst->configurations_count, pSrc);
	OCT_B2DNTOHS(pDst->current_configuration, pSrc);

	AVB_RC_TRACE_RET(OPENAVB_AVDECC_SUCCESS, AVB_TRACE_AEM);
}


////////////////////////////////
// Public functions
////////////////////////////////
extern DLL_EXPORT openavb_aem_descriptor_entity_t *openavbAemDescriptorEntityNew()
{
	AVB_TRACE_ENTRY(AVB_TRACE_AEM);

	openavb_aem_descriptor_entity_t *pDescriptor;

	pDescriptor = malloc(OPENAVB_DESCRIPTOR_ENTITY_BASE_LENGTH);

	if (!pDescriptor) {
		AVB_RC_LOG(AVB_RC(OPENAVB_AVDECC_FAILURE | OPENAVB_RC_OUT_OF_MEMORY));
		AVB_TRACE_EXIT(AVB_TRACE_AEM);
		return NULL;
	}
	memset(pDescriptor, 0, OPENAVB_DESCRIPTOR_ENTITY_BASE_LENGTH);

	pDescriptor->descriptorPvtPtr = malloc(sizeof(*pDescriptor->descriptorPvtPtr));
	if (!pDescriptor->descriptorPvtPtr) {
		free(pDescriptor);
		pDescriptor = NULL;
		AVB_RC_LOG(AVB_RC(OPENAVB_AVDECC_FAILURE | OPENAVB_RC_OUT_OF_MEMORY));
		AVB_TRACE_EXIT(AVB_TRACE_AEM);
		return FALSE;
	}

	pDescriptor->descriptorPvtPtr->size = sizeof(openavb_aem_descriptor_entity_t);
	pDescriptor->descriptorPvtPtr->bTopLevel = TRUE;
	pDescriptor->descriptorPvtPtr->toBuf = openavbAemDescriptorEntityToBuf;
	pDescriptor->descriptorPvtPtr->fromBuf = openavbAemDescriptorEntityFromBuf;

	pDescriptor->descriptor_type = OPENAVB_AEM_DESCRIPTOR_ENTITY;
	pDescriptor->descriptor_index = 0;

	AVB_TRACE_EXIT(AVB_TRACE_AEM);
	return pDescriptor;
}

extern DLL_EXPORT bool openavbAemDescriptorEntitySet_entity_id(openavb_aem_descriptor_entity_t *pDescriptor, char *aMacAddr, U8 *nMacAddr, U16 id)
{
	AVB_TRACE_ENTRY(AVB_TRACE_AEM);

	if (!pDescriptor) {
		AVB_RC_LOG(AVB_RC(OPENAVB_AVDECC_FAILURE | OPENAVB_RC_INVALID_ARGUMENT));
		AVB_TRACE_EXIT(AVB_TRACE_AEM);
		return FALSE;
	}

	struct ether_addr macAddrBuffer;
	if (aMacAddr) {
		// If an ascii mac address is passed in parse and use it.
		memset(macAddrBuffer.ether_addr_octet, 0, sizeof(macAddrBuffer));

		if (!ether_aton_r(aMacAddr, &macAddrBuffer)) {
			AVB_RC_LOG(AVB_RC(OPENAVB_AVDECC_FAILURE | OPENAVBAVDECC_RC_PARSING_MAC_ADDRESS));
			AVB_TRACE_EXIT(AVB_TRACE_AEM);
			return FALSE;
		}
		memcpy(pDescriptor->entity_id + 2, macAddrBuffer.ether_addr_octet, sizeof(macAddrBuffer.ether_addr_octet));
	}
	else if (nMacAddr) {
		// If a network mac address is passed in use it.
		memcpy(pDescriptor->entity_id + 2, nMacAddr, sizeof(pDescriptor->entity_id));
	}
	else {
		// If no mac address is passed in obtain it from the stack.
		memcpy(pDescriptor->entity_id + 2, openavbAVDECCMacAddr.ether_addr_octet, sizeof(openavbAVDECCMacAddr));
	}

//	*(U16 *)(pDescriptor->entity_id) = htons(id);
	U16 tmpU16 = htons(id);
	memcpy(pDescriptor->entity_id, &tmpU16, sizeof(tmpU16));

	AVB_TRACE_EXIT(AVB_TRACE_AEM);
	return TRUE;
}


