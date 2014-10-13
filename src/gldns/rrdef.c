/* rrdef.c
 *
 * access functions to rr definitions list.
 * a Net::DNS like library for C
 * LibDNS Team @ NLnet Labs
 *
 * (c) NLnet Labs, 2004-2006
 * See the file LICENSE for the license
 */
/**
 * \file
 *
 * Defines resource record types and constants.
 */
#include "config.h"
#include "gldns/rrdef.h"
#include "gldns/parseutil.h"

/* classes  */
static gldns_lookup_table gldns_rr_classes_data[] = {
        { GLDNS_RR_CLASS_IN, "IN" },
        { GLDNS_RR_CLASS_CH, "CH" },
        { GLDNS_RR_CLASS_HS, "HS" },
        { GLDNS_RR_CLASS_NONE, "NONE" },
        { GLDNS_RR_CLASS_ANY, "ANY" },
        { 0, NULL }
};
gldns_lookup_table* gldns_rr_classes = gldns_rr_classes_data;

/* types */
static const gldns_rdf_type type_0_wireformat[] = { GLDNS_RDF_TYPE_UNKNOWN };
static const gldns_rdf_type type_a_wireformat[] = { GLDNS_RDF_TYPE_A };
static const gldns_rdf_type type_ns_wireformat[] = { GLDNS_RDF_TYPE_DNAME };
static const gldns_rdf_type type_md_wireformat[] = { GLDNS_RDF_TYPE_DNAME };
static const gldns_rdf_type type_mf_wireformat[] = { GLDNS_RDF_TYPE_DNAME };
static const gldns_rdf_type type_cname_wireformat[] = { GLDNS_RDF_TYPE_DNAME };
static const gldns_rdf_type type_soa_wireformat[] = {
	GLDNS_RDF_TYPE_DNAME, GLDNS_RDF_TYPE_DNAME, GLDNS_RDF_TYPE_INT32, 
	GLDNS_RDF_TYPE_PERIOD, GLDNS_RDF_TYPE_PERIOD, GLDNS_RDF_TYPE_PERIOD,
	GLDNS_RDF_TYPE_PERIOD
};
static const gldns_rdf_type type_mb_wireformat[] = { GLDNS_RDF_TYPE_DNAME };
static const gldns_rdf_type type_mg_wireformat[] = { GLDNS_RDF_TYPE_DNAME };
static const gldns_rdf_type type_mr_wireformat[] = { GLDNS_RDF_TYPE_DNAME };
static const gldns_rdf_type type_wks_wireformat[] = {
	GLDNS_RDF_TYPE_A, GLDNS_RDF_TYPE_WKS
};
static const gldns_rdf_type type_ptr_wireformat[] = { GLDNS_RDF_TYPE_DNAME };
static const gldns_rdf_type type_hinfo_wireformat[] = {
	GLDNS_RDF_TYPE_STR, GLDNS_RDF_TYPE_STR
};
static const gldns_rdf_type type_minfo_wireformat[] = {
	GLDNS_RDF_TYPE_DNAME, GLDNS_RDF_TYPE_DNAME
};
static const gldns_rdf_type type_mx_wireformat[] = {
	GLDNS_RDF_TYPE_INT16, GLDNS_RDF_TYPE_DNAME
};
static const gldns_rdf_type type_rp_wireformat[] = {
	GLDNS_RDF_TYPE_DNAME, GLDNS_RDF_TYPE_DNAME
};
static const gldns_rdf_type type_afsdb_wireformat[] = {
	GLDNS_RDF_TYPE_INT16, GLDNS_RDF_TYPE_DNAME
};
static const gldns_rdf_type type_x25_wireformat[] = { GLDNS_RDF_TYPE_STR };
static const gldns_rdf_type type_isdn_wireformat[] = {
	GLDNS_RDF_TYPE_STR, GLDNS_RDF_TYPE_STR
};
static const gldns_rdf_type type_rt_wireformat[] = {
	GLDNS_RDF_TYPE_INT16, GLDNS_RDF_TYPE_DNAME
};
static const gldns_rdf_type type_nsap_wireformat[] = {
	GLDNS_RDF_TYPE_NSAP
};
static const gldns_rdf_type type_nsap_ptr_wireformat[] = {
	GLDNS_RDF_TYPE_STR
};
static const gldns_rdf_type type_sig_wireformat[] = {
	GLDNS_RDF_TYPE_TYPE, GLDNS_RDF_TYPE_ALG, GLDNS_RDF_TYPE_INT8, GLDNS_RDF_TYPE_INT32,
	GLDNS_RDF_TYPE_TIME, GLDNS_RDF_TYPE_TIME, GLDNS_RDF_TYPE_INT16,
	GLDNS_RDF_TYPE_DNAME, GLDNS_RDF_TYPE_B64
};
static const gldns_rdf_type type_key_wireformat[] = {
	GLDNS_RDF_TYPE_INT16, GLDNS_RDF_TYPE_INT8, GLDNS_RDF_TYPE_INT8, GLDNS_RDF_TYPE_B64
};
static const gldns_rdf_type type_px_wireformat[] = {
	GLDNS_RDF_TYPE_INT16, GLDNS_RDF_TYPE_DNAME, GLDNS_RDF_TYPE_DNAME
};
static const gldns_rdf_type type_gpos_wireformat[] = {
	GLDNS_RDF_TYPE_STR, GLDNS_RDF_TYPE_STR, GLDNS_RDF_TYPE_STR
};
static const gldns_rdf_type type_aaaa_wireformat[] = { GLDNS_RDF_TYPE_AAAA };
static const gldns_rdf_type type_loc_wireformat[] = { GLDNS_RDF_TYPE_LOC };
static const gldns_rdf_type type_nxt_wireformat[] = {
	GLDNS_RDF_TYPE_DNAME, GLDNS_RDF_TYPE_UNKNOWN
};
static const gldns_rdf_type type_eid_wireformat[] = {
	GLDNS_RDF_TYPE_HEX
};
static const gldns_rdf_type type_nimloc_wireformat[] = {
	GLDNS_RDF_TYPE_HEX
};
static const gldns_rdf_type type_srv_wireformat[] = {
	GLDNS_RDF_TYPE_INT16, GLDNS_RDF_TYPE_INT16, GLDNS_RDF_TYPE_INT16, GLDNS_RDF_TYPE_DNAME
};
static const gldns_rdf_type type_atma_wireformat[] = {
	GLDNS_RDF_TYPE_ATMA
};
static const gldns_rdf_type type_naptr_wireformat[] = {
	GLDNS_RDF_TYPE_INT16, GLDNS_RDF_TYPE_INT16, GLDNS_RDF_TYPE_STR, GLDNS_RDF_TYPE_STR, GLDNS_RDF_TYPE_STR, GLDNS_RDF_TYPE_DNAME
};
static const gldns_rdf_type type_kx_wireformat[] = {
	GLDNS_RDF_TYPE_INT16, GLDNS_RDF_TYPE_DNAME
};
static const gldns_rdf_type type_cert_wireformat[] = {
	 GLDNS_RDF_TYPE_CERT_ALG, GLDNS_RDF_TYPE_INT16, GLDNS_RDF_TYPE_ALG, GLDNS_RDF_TYPE_B64
};
static const gldns_rdf_type type_a6_wireformat[] = { GLDNS_RDF_TYPE_UNKNOWN };
static const gldns_rdf_type type_dname_wireformat[] = { GLDNS_RDF_TYPE_DNAME };
static const gldns_rdf_type type_sink_wireformat[] = { GLDNS_RDF_TYPE_INT8,
	GLDNS_RDF_TYPE_INT8, GLDNS_RDF_TYPE_INT8, GLDNS_RDF_TYPE_B64
};
static const gldns_rdf_type type_apl_wireformat[] = {
	GLDNS_RDF_TYPE_APL
};
static const gldns_rdf_type type_ds_wireformat[] = {
	GLDNS_RDF_TYPE_INT16, GLDNS_RDF_TYPE_ALG, GLDNS_RDF_TYPE_INT8, GLDNS_RDF_TYPE_HEX
};
static const gldns_rdf_type type_sshfp_wireformat[] = {
	GLDNS_RDF_TYPE_INT8, GLDNS_RDF_TYPE_INT8, GLDNS_RDF_TYPE_HEX
};
static const gldns_rdf_type type_ipseckey_wireformat[] = {
	GLDNS_RDF_TYPE_IPSECKEY
};
static const gldns_rdf_type type_rrsig_wireformat[] = {
	GLDNS_RDF_TYPE_TYPE, GLDNS_RDF_TYPE_ALG, GLDNS_RDF_TYPE_INT8, GLDNS_RDF_TYPE_INT32,
	GLDNS_RDF_TYPE_TIME, GLDNS_RDF_TYPE_TIME, GLDNS_RDF_TYPE_INT16, GLDNS_RDF_TYPE_DNAME, GLDNS_RDF_TYPE_B64
};
static const gldns_rdf_type type_nsec_wireformat[] = {
	GLDNS_RDF_TYPE_DNAME, GLDNS_RDF_TYPE_NSEC
};
static const gldns_rdf_type type_dhcid_wireformat[] = {
	GLDNS_RDF_TYPE_B64
};
static const gldns_rdf_type type_talink_wireformat[] = {
	GLDNS_RDF_TYPE_DNAME, GLDNS_RDF_TYPE_DNAME
};
/* nsec3 is some vars, followed by same type of data of nsec */
static const gldns_rdf_type type_nsec3_wireformat[] = {
/*	GLDNS_RDF_TYPE_NSEC3_VARS, GLDNS_RDF_TYPE_NSEC3_NEXT_OWNER, GLDNS_RDF_TYPE_NSEC*/
	GLDNS_RDF_TYPE_INT8, GLDNS_RDF_TYPE_INT8, GLDNS_RDF_TYPE_INT16, GLDNS_RDF_TYPE_NSEC3_SALT, GLDNS_RDF_TYPE_NSEC3_NEXT_OWNER, GLDNS_RDF_TYPE_NSEC
};

static const gldns_rdf_type type_nsec3param_wireformat[] = {
/*	GLDNS_RDF_TYPE_NSEC3_PARAMS_VARS*/
	GLDNS_RDF_TYPE_INT8,
	GLDNS_RDF_TYPE_INT8,
	GLDNS_RDF_TYPE_INT16,
	GLDNS_RDF_TYPE_NSEC3_SALT
};

static const gldns_rdf_type type_dnskey_wireformat[] = {
	GLDNS_RDF_TYPE_INT16,
	GLDNS_RDF_TYPE_INT8,
	GLDNS_RDF_TYPE_ALG,
	GLDNS_RDF_TYPE_B64
};
static const gldns_rdf_type type_tkey_wireformat[] = {
	GLDNS_RDF_TYPE_DNAME,
	GLDNS_RDF_TYPE_TIME,
	GLDNS_RDF_TYPE_TIME,
	GLDNS_RDF_TYPE_INT16,
	GLDNS_RDF_TYPE_INT16,
	GLDNS_RDF_TYPE_INT16_DATA,
	GLDNS_RDF_TYPE_INT16_DATA,
};
static const gldns_rdf_type type_tsig_wireformat[] = {
	GLDNS_RDF_TYPE_DNAME,
	GLDNS_RDF_TYPE_TSIGTIME,
	GLDNS_RDF_TYPE_INT16,
	GLDNS_RDF_TYPE_INT16_DATA,
	GLDNS_RDF_TYPE_INT16,
	GLDNS_RDF_TYPE_INT16,
	GLDNS_RDF_TYPE_INT16_DATA
};
static const gldns_rdf_type type_tlsa_wireformat[] = {
	GLDNS_RDF_TYPE_INT8,
	GLDNS_RDF_TYPE_INT8,
	GLDNS_RDF_TYPE_INT8,
	GLDNS_RDF_TYPE_HEX
};
static const gldns_rdf_type type_hip_wireformat[] = {
	GLDNS_RDF_TYPE_HIP
};
static const gldns_rdf_type type_nid_wireformat[] = {
	GLDNS_RDF_TYPE_INT16,
	GLDNS_RDF_TYPE_ILNP64
};
static const gldns_rdf_type type_l32_wireformat[] = {
	GLDNS_RDF_TYPE_INT16,
	GLDNS_RDF_TYPE_A
};
static const gldns_rdf_type type_l64_wireformat[] = {
	GLDNS_RDF_TYPE_INT16,
	GLDNS_RDF_TYPE_ILNP64
};
static const gldns_rdf_type type_lp_wireformat[] = {
	GLDNS_RDF_TYPE_INT16,
	GLDNS_RDF_TYPE_DNAME
};
static const gldns_rdf_type type_eui48_wireformat[] = {
	GLDNS_RDF_TYPE_EUI48
};
static const gldns_rdf_type type_eui64_wireformat[] = {
	GLDNS_RDF_TYPE_EUI64
};
#ifdef DRAFT_RRTYPES
static const gldns_rdf_type type_uri_wireformat[] = {
	GLDNS_RDF_TYPE_INT16,
	GLDNS_RDF_TYPE_INT16,
	GLDNS_RDF_TYPE_LONG_STR
};
#endif
static const gldns_rdf_type type_caa_wireformat[] = {
	GLDNS_RDF_TYPE_INT8,
	GLDNS_RDF_TYPE_TAG,
	GLDNS_RDF_TYPE_LONG_STR
};

/* All RR's defined in 1035 are well known and can thus
 * be compressed. See RFC3597. These RR's are:
 * CNAME HINFO MB MD MF MG MINFO MR MX NULL NS PTR SOA TXT
 */
static gldns_rr_descriptor rdata_field_descriptors[] = {
	/* 0 */
	{ 0, NULL, 0, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 1 */
	{GLDNS_RR_TYPE_A, "A", 1, 1, type_a_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 2 */
	{GLDNS_RR_TYPE_NS, "NS", 1, 1, type_ns_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_COMPRESS, 1 },
	/* 3 */
	{GLDNS_RR_TYPE_MD, "MD", 1, 1, type_md_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_COMPRESS, 1 },
	/* 4 */
	{GLDNS_RR_TYPE_MF, "MF", 1, 1, type_mf_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_COMPRESS, 1 },
	/* 5 */
	{GLDNS_RR_TYPE_CNAME, "CNAME", 1, 1, type_cname_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_COMPRESS, 1 },
	/* 6 */
	{GLDNS_RR_TYPE_SOA, "SOA", 7, 7, type_soa_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_COMPRESS, 2 },
	/* 7 */
	{GLDNS_RR_TYPE_MB, "MB", 1, 1, type_mb_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_COMPRESS, 1 },
	/* 8 */
	{GLDNS_RR_TYPE_MG, "MG", 1, 1, type_mg_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_COMPRESS, 1 },
	/* 9 */
	{GLDNS_RR_TYPE_MR, "MR", 1, 1, type_mr_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_COMPRESS, 1 },
	/* 10 */
	{GLDNS_RR_TYPE_NULL, "NULL", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 11 */
	{GLDNS_RR_TYPE_WKS, "WKS", 2, 2, type_wks_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 12 */
	{GLDNS_RR_TYPE_PTR, "PTR", 1, 1, type_ptr_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_COMPRESS, 1 },
	/* 13 */
	{GLDNS_RR_TYPE_HINFO, "HINFO", 2, 2, type_hinfo_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 14 */
	{GLDNS_RR_TYPE_MINFO, "MINFO", 2, 2, type_minfo_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_COMPRESS, 2 },
	/* 15 */
	{GLDNS_RR_TYPE_MX, "MX", 2, 2, type_mx_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_COMPRESS, 1 },
	/* 16 */
	{GLDNS_RR_TYPE_TXT, "TXT", 1, 0, NULL, GLDNS_RDF_TYPE_STR, GLDNS_RR_NO_COMPRESS, 0 },
	/* 17 */
	{GLDNS_RR_TYPE_RP, "RP", 2, 2, type_rp_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 2 },
	/* 18 */
	{GLDNS_RR_TYPE_AFSDB, "AFSDB", 2, 2, type_afsdb_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 1 },
	/* 19 */
	{GLDNS_RR_TYPE_X25, "X25", 1, 1, type_x25_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 20 */
	{GLDNS_RR_TYPE_ISDN, "ISDN", 1, 2, type_isdn_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 21 */
	{GLDNS_RR_TYPE_RT, "RT", 2, 2, type_rt_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 1 },
	/* 22 */
	{GLDNS_RR_TYPE_NSAP, "NSAP", 1, 1, type_nsap_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 23 */
	{GLDNS_RR_TYPE_NSAP_PTR, "NSAP-PTR", 1, 1, type_nsap_ptr_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 24 */
	{GLDNS_RR_TYPE_SIG, "SIG", 9, 9, type_sig_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 1 },
	/* 25 */
	{GLDNS_RR_TYPE_KEY, "KEY", 4, 4, type_key_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 26 */
	{GLDNS_RR_TYPE_PX, "PX", 3, 3, type_px_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 2 },
	/* 27 */
	{GLDNS_RR_TYPE_GPOS, "GPOS", 3, 3, type_gpos_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 28 */
	{GLDNS_RR_TYPE_AAAA, "AAAA", 1, 1, type_aaaa_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 29 */
	{GLDNS_RR_TYPE_LOC, "LOC", 1, 1, type_loc_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 30 */
	{GLDNS_RR_TYPE_NXT, "NXT", 2, 2, type_nxt_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 1 },
	/* 31 */
	{GLDNS_RR_TYPE_EID, "EID", 1, 1, type_eid_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 32 */
	{GLDNS_RR_TYPE_NIMLOC, "NIMLOC", 1, 1, type_nimloc_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 33 */
	{GLDNS_RR_TYPE_SRV, "SRV", 4, 4, type_srv_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 1 },
	/* 34 */
	{GLDNS_RR_TYPE_ATMA, "ATMA", 1, 1, type_atma_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 35 */
	{GLDNS_RR_TYPE_NAPTR, "NAPTR", 6, 6, type_naptr_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 1 },
	/* 36 */
	{GLDNS_RR_TYPE_KX, "KX", 2, 2, type_kx_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 1 },
	/* 37 */
	{GLDNS_RR_TYPE_CERT, "CERT", 4, 4, type_cert_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 38 */
	{GLDNS_RR_TYPE_A6, "A6", 1, 1, type_a6_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 39 */
	{GLDNS_RR_TYPE_DNAME, "DNAME", 1, 1, type_dname_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 1 },
	/* 40 */
	{GLDNS_RR_TYPE_SINK, "SINK", 1, 1, type_sink_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 41 */
	{GLDNS_RR_TYPE_OPT, "OPT", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 42 */
	{GLDNS_RR_TYPE_APL, "APL", 0, 0, type_apl_wireformat, GLDNS_RDF_TYPE_APL, GLDNS_RR_NO_COMPRESS, 0 },
	/* 43 */
	{GLDNS_RR_TYPE_DS, "DS", 4, 4, type_ds_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 44 */
	{GLDNS_RR_TYPE_SSHFP, "SSHFP", 3, 3, type_sshfp_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 45 */
	{GLDNS_RR_TYPE_IPSECKEY, "IPSECKEY", 1, 1, type_ipseckey_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 46 */
	{GLDNS_RR_TYPE_RRSIG, "RRSIG", 9, 9, type_rrsig_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 1 },
	/* 47 */
	{GLDNS_RR_TYPE_NSEC, "NSEC", 1, 2, type_nsec_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 1 },
	/* 48 */
	{GLDNS_RR_TYPE_DNSKEY, "DNSKEY", 4, 4, type_dnskey_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 49 */
	{GLDNS_RR_TYPE_DHCID, "DHCID", 1, 1, type_dhcid_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 50 */
	{GLDNS_RR_TYPE_NSEC3, "NSEC3", 5, 6, type_nsec3_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 51 */
	{GLDNS_RR_TYPE_NSEC3PARAM, "NSEC3PARAM", 4, 4, type_nsec3param_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 52 */
	{GLDNS_RR_TYPE_TLSA, "TLSA", 4, 4, type_tlsa_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },

{GLDNS_RR_TYPE_NULL, "TYPE53", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE54", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
        /* 55
	 * Hip ends with 0 or more Rendezvous Servers represented as dname's.
	 * Hence the GLDNS_RDF_TYPE_DNAME _variable field and the _maximum field
	 * set to 0.
	 */
	{GLDNS_RR_TYPE_HIP, "HIP", 1, 1, type_hip_wireformat, GLDNS_RDF_TYPE_DNAME, GLDNS_RR_NO_COMPRESS, 0 },

#ifdef DRAFT_RRTYPES
	/* 56 */
	{GLDNS_RR_TYPE_NINFO, "NINFO", 1, 0, NULL, GLDNS_RDF_TYPE_STR, GLDNS_RR_NO_COMPRESS, 0 },
	/* 57 */
	{GLDNS_RR_TYPE_RKEY, "RKEY", 4, 4, type_key_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
#else
{GLDNS_RR_TYPE_NULL, "TYPE56", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE57", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
#endif
	/* 58 */
	{GLDNS_RR_TYPE_TALINK, "TALINK", 2, 2, type_talink_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 2 },

	/* 59 */
	{GLDNS_RR_TYPE_CDS, "CDS", 4, 4, type_ds_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 60 */
	{GLDNS_RR_TYPE_CDNSKEY, "CDNSKEY", 4, 4, type_dnskey_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE61", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE62", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE63", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE64", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE65", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE66", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE67", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE68", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE69", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE70", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE71", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE72", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE73", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE74", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE75", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE76", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE77", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE78", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE79", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE80", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE81", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE82", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE83", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE84", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE85", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE86", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE87", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE88", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE89", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE90", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE91", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE92", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE93", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE94", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE95", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE96", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE97", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE98", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },

	/* 99 */
	{GLDNS_RR_TYPE_SPF,  "SPF", 1, 0, NULL, GLDNS_RDF_TYPE_STR, GLDNS_RR_NO_COMPRESS, 0 },

	/* UINFO  [IANA-Reserved] */
{GLDNS_RR_TYPE_NULL, "TYPE100", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* UID    [IANA-Reserved] */
{GLDNS_RR_TYPE_NULL, "TYPE101", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* GID    [IANA-Reserved] */
{GLDNS_RR_TYPE_NULL, "TYPE102", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* UNSPEC [IANA-Reserved] */
{GLDNS_RR_TYPE_NULL, "TYPE103", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },

	/* 104 */
	{GLDNS_RR_TYPE_NID, "NID", 2, 2, type_nid_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 105 */
	{GLDNS_RR_TYPE_L32, "L32", 2, 2, type_l32_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 106 */
	{GLDNS_RR_TYPE_L64, "L64", 2, 2, type_l64_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 107 */
	{GLDNS_RR_TYPE_LP, "LP", 2, 2, type_lp_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 1 },

	/* 108 */
	{GLDNS_RR_TYPE_EUI48, "EUI48", 1, 1, type_eui48_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* 109 */
	{GLDNS_RR_TYPE_EUI64, "EUI64", 1, 1, type_eui64_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },

{GLDNS_RR_TYPE_NULL, "TYPE110", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE111", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE112", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE113", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE114", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE115", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE116", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE117", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE118", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE119", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE120", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE121", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE122", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE123", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE124", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE125", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE126", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE127", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE128", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE129", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE130", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE131", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE132", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE133", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE134", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE135", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE136", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE137", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE138", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE139", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE140", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE141", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE142", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE143", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE144", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE145", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE146", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE147", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE148", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE149", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE150", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE151", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE152", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE153", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE154", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE155", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE156", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE157", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE158", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE159", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE160", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE161", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE162", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE163", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE164", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE165", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE166", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE167", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE168", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE169", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE170", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE171", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE172", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE173", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE174", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE175", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE176", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE177", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE178", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE179", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE180", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE181", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE182", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE183", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE184", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE185", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE186", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE187", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE188", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE189", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE190", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE191", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE192", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE193", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE194", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE195", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE196", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE197", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE198", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE199", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE200", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE201", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE202", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE203", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE204", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE205", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE206", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE207", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE208", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE209", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE210", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE211", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE212", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE213", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE214", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE215", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE216", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE217", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE218", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE219", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE220", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE221", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE222", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE223", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE224", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE225", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE226", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE227", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE228", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE229", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE230", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE231", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE232", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE233", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE234", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE235", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE236", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE237", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE238", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE239", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE240", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE241", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE242", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE243", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE244", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE245", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE246", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE247", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
{GLDNS_RR_TYPE_NULL, "TYPE248", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },

	/* GLDNS_RDF_TYPE_INT16_DATA takes two fields (length and data) as one.
	 * So, unlike RFC 2930 spec, we have 7 min/max rdf's i.s.o. 8/9.
	 */
	/* 249 */
	{GLDNS_RR_TYPE_TKEY, "TKEY", 7, 7, type_tkey_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 1 },
	/* GLDNS_RDF_TYPE_INT16_DATA takes two fields (length and data) as one.
	 * So, unlike RFC 2930 spec, we have 7 min/max rdf's i.s.o. 8/9.
	 */
	/* 250 */
	{GLDNS_RR_TYPE_TSIG, "TSIG", 7, 7, type_tsig_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 1 },

	/* IXFR: A request for a transfer of an incremental zone transfer */
{GLDNS_RR_TYPE_IXFR, "IXFR", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* AXFR: A request for a transfer of an entire zone */
{GLDNS_RR_TYPE_AXFR, "AXFR", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* MAILB: A request for mailbox-related records (MB, MG or MR) */
{GLDNS_RR_TYPE_MAILB, "MAILB", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* MAILA: A request for mail agent RRs (Obsolete - see MX) */
{GLDNS_RR_TYPE_MAILA, "MAILA", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
	/* ANY: A request for all (available) records */
{GLDNS_RR_TYPE_ANY, "ANY", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },

#ifdef DRAFT_RRTYPES
	/* 256 */
	{GLDNS_RR_TYPE_URI, "URI", 3, 3, type_uri_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
#else
{GLDNS_RR_TYPE_NULL, "TYPE256", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
#endif
	/* 257 */
	{GLDNS_RR_TYPE_CAA, "CAA", 3, 3, type_caa_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },

/* split in array, no longer contiguous */

#ifdef DRAFT_RRTYPES
	/* 32768 */
	{GLDNS_RR_TYPE_TA, "TA", 4, 4, type_ds_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
#else
{GLDNS_RR_TYPE_NULL, "TYPE32768", 1, 1, type_0_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 },
#endif
	/* 32769 */
	{GLDNS_RR_TYPE_DLV, "DLV", 4, 4, type_ds_wireformat, GLDNS_RDF_TYPE_NONE, GLDNS_RR_NO_COMPRESS, 0 }
};

/**
 * \def GLDNS_RDATA_FIELD_DESCRIPTORS_COUNT
 * computes the number of rdata fields
 */
#define GLDNS_RDATA_FIELD_DESCRIPTORS_COUNT \
	(sizeof(rdata_field_descriptors)/sizeof(rdata_field_descriptors[0]))

const gldns_rr_descriptor *
gldns_rr_descript(uint16_t type)
{
	size_t i;
	if (type < GLDNS_RDATA_FIELD_DESCRIPTORS_COMMON) {
		return &rdata_field_descriptors[type];
	} else {
		/* because not all array index equals type code */
		for (i = GLDNS_RDATA_FIELD_DESCRIPTORS_COMMON;
		     i < GLDNS_RDATA_FIELD_DESCRIPTORS_COUNT;
		     i++) {
		        if (rdata_field_descriptors[i]._type == type) {
		     		return &rdata_field_descriptors[i];
			}
		}
                return &rdata_field_descriptors[0];
	}
}

size_t
gldns_rr_descriptor_minimum(const gldns_rr_descriptor *descriptor)
{
	if (descriptor) {
		return descriptor->_minimum;
	} else {
		return 0;
	}
}

size_t
gldns_rr_descriptor_maximum(const gldns_rr_descriptor *descriptor)
{
	if (descriptor) {
		if (descriptor->_variable != GLDNS_RDF_TYPE_NONE) {
			return 65535; /* cannot be more than 64k */
		} else {
			return descriptor->_maximum;
		}
	} else {
		return 0;
	}
}

gldns_rdf_type
gldns_rr_descriptor_field_type(const gldns_rr_descriptor *descriptor,
                              size_t index)
{
	assert(descriptor != NULL);
	assert(index < descriptor->_maximum
	       || descriptor->_variable != GLDNS_RDF_TYPE_NONE);
	if (index < descriptor->_maximum) {
		return descriptor->_wireformat[index];
	} else {
		return descriptor->_variable;
	}
}

gldns_rr_type
gldns_get_rr_type_by_name(const char *name)
{
	unsigned int i;
	const char *desc_name;
	const gldns_rr_descriptor *desc;

	/* TYPEXX representation */
	if (strlen(name) > 4 && strncasecmp(name, "TYPE", 4) == 0) {
		return atoi(name + 4);
	}

	/* Normal types */
	for (i = 0; i < (unsigned int) GLDNS_RDATA_FIELD_DESCRIPTORS_COUNT; i++) {
		desc = &rdata_field_descriptors[i];
		desc_name = desc->_name;
		if(desc_name &&
		   strlen(name) == strlen(desc_name) &&
		   strncasecmp(name, desc_name, strlen(desc_name)) == 0) {
			/* because not all array index equals type code */
			return desc->_type;
		}
	}

	/* special cases for query types */
	if (strlen(name) == 4 && strncasecmp(name, "IXFR", 4) == 0) {
		return 251;
	} else if (strlen(name) == 4 && strncasecmp(name, "AXFR", 4) == 0) {
		return 252;
	} else if (strlen(name) == 5 && strncasecmp(name, "MAILB", 5) == 0) {
		return 253;
	} else if (strlen(name) == 5 && strncasecmp(name, "MAILA", 5) == 0) {
		return 254;
	} else if (strlen(name) == 3 && strncasecmp(name, "ANY", 3) == 0) {
		return 255;
	}

	return 0;
}

gldns_rr_class
gldns_get_rr_class_by_name(const char *name)
{
	gldns_lookup_table *lt;

	/* CLASSXX representation */
	if (strlen(name) > 5 && strncasecmp(name, "CLASS", 5) == 0) {
		return atoi(name + 5);
	}

	/* Normal types */
	lt = gldns_lookup_by_name(gldns_rr_classes, name);
	if (lt) {
		return lt->id;
	}
	return 0;
}