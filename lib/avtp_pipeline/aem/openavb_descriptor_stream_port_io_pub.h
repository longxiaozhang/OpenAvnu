/*
 ******************************************************************
 * COPYRIGHT � Symphony Teleca
 *----------------------------------------------------------------*
 * MODULE : AEM - AVDECC Stream Port IO Descriptor Public Interface
 *
 * PROGRAMMER : Ken Carlino (Triple Play Integration)
 * DATE :       20-Dec-2013
 * VERSION :    1.0
 *
 *----------------------------------------------------------------*
 *
 * MODULE SUMMARY : Pulbic Interface for the Stream Port IO Desciptor
 *
 *----------------------------------------------------------------*
 *
 * MODIFICATION RECORDS
 *
 ******************************************************************
 */

#ifndef OPENAVB_DESCRIPTOR_STREAM_PORT_IO_PUB_H
#define OPENAVB_DESCRIPTOR_STREAM_PORT_IO_PUB_H 1

#include "openavb_types_pub.h"
#include "openavb_aem_types_pub.h"
#include "openavb_aem_pub.h"

// STREAM PORT IO Descriptor IEEE Std 1722.1-2013 clause 7.2.13
typedef struct {
	openavb_descriptor_pvt_ptr_t descriptorPvtPtr;

	U16 descriptor_type;
	U16 descriptor_index;
	U16 clock_domain_index;
	U16 port_flags;
	U16 number_of_controls;
	U16 base_control;
	U16 number_of_clusters;
	U16 base_cluster;
	U16 number_of_maps;
	U16 base_map;
} openavb_aem_descriptor_stream_port_io_t;

openavb_aem_descriptor_stream_port_io_t *openavbAemDescriptorStreamPortInputNew(void);
openavb_aem_descriptor_stream_port_io_t *openavbAemDescriptorStreamPortOutputNew(void);

#endif // OPENAVB_DESCRIPTOR_STREAM_PORT_IO_PUB_H
