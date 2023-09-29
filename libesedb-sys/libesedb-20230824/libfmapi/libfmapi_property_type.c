/*
 * Property type functions
 *
 * Copyright (C) 2009-2023, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <memory.h>
#include <narrow_string.h>
#include <types.h>

#include "libfmapi_class_identifier.h"
#include "libfmapi_property_type.h"

#if defined( HAVE_DEBUG_OUTPUT )

/* The message envelope property types (0x0001 - 0x0bff)
 */
libfmapi_property_type_t libfmapi_message_envelope_property_types[ ] = {
	{ 0x0001, 0x0003, "PidTagAcknowledgementMode",					"Acknowledgment mode" },
	{ 0x0002, 0x000b, "PidTagAlternateRecipientAllowed",				"Alternate recipient allowed" },
	{ 0x0003, 0x0102, "PidTagAuthorizingUsers",					"Authorized users" },
	{ 0x0004, 0x001e, "PidTagAutoForwardComment",					"Auto forward comment" },
	{ 0x0005, 0x000b, "PidTagAutoForwarded",					"Auto forwarded" },
	{ 0x0006, 0x0102, "PidTagContentConfidentialityAlgorithmId",			"Content confidentiality algorithm identifier" },
	{ 0x0007, 0x0102, "PidTagContentCorrelator",					"Original content correlator" },
	{ 0x0008, 0x001e, "PidTagContentIdentifier",					"Content identifier" },
	{ 0x0009, 0x0003, "PidTagContentLength",					"Content length" },
	{ 0x000a, 0x000b, "PidTagContentReturnRequested",				"Content return requested" },
	{ 0x000b, 0x0102, "PidTagConversationKey",					"Conversation key" },
	{ 0x000c, 0x0102, "PidTagConversionEits",					"Conversion encoded information types" },
	{ 0x000d, 0x000b, "PidTagConversionWithLossProhibited",				"Text conversions that loose information is prohibited" },
	{ 0x000e, 0x0102, "PidTagConvertedEits",					"Encoded information types (EITS) conversation identifier" },
	{ 0x000f, 0x0040, "PidTagDeferredDeliveryTime",					"Sender requested delivery date and time" },
	{ 0x0010, 0x0040, "PidTagDeliverTime",						"Message delivery time" },
	{ 0x0011, 0x0003, "PidTagDiscardReason",					"Message discard reason" },
	{ 0x0012, 0x000b, "PidTagDisclosureOfRecipients",				"Disclosure of recipient allowed" },
	{ 0x0013, 0x0102, "PidTagDistributionListExpansionHistory",			"Distribution list expansion history" },
	{ 0x0014, 0x000b, "PidTagDistributionListExpansionProhibited",			"Expansion of distribution list is prohibited" },
	{ 0x0015, 0x0040, "PidTagExpiryTime",						"Message expiry time" },
	{ 0x0016, 0x000b, "PidTagImplicitConversionProhibited",				"Implicit message text conversions prohibited" },
	{ 0x0017, 0x0003, "PidTagImportance",						"Importance" },
	{ 0x0018, 0x0102, "PR_IPM_ID",							"Interpersonal message X400 identifier" },
	{ 0x0019, 0x0040, "PidTagLatestDeliveryTime",					"Latest message delivery time" },
	{ 0x001a, 0x001e, "PidTagMessageClass",						"Message class" },
	{ 0x001b, 0x0102, "PidTagMessageDeliveryId",					"Message delivery identifier" },
	{ 0x001e, 0x0102, "PidTagMessageSecurityLabel",					"Message security label" },
	{ 0x001f, 0x0102, "PidTagObsoletedMessageIds",					"Obsolete message identifiers" },
	{ 0x0020, 0x0102, "PidTagOriginallyIntendedRecipientName",			"Originally intended recipient name" },
	{ 0x0021, 0x0102, "PidTagOriginalEits",						"Message text original encoded information types (EITS)" },
	{ 0x0022, 0x0102, "PidTagOriginatorCertificate",				"Originator certificate" },
	{ 0x0023, 0x000b, "PidTagOriginatorDeliveryReportRequested",			"Originator delivery report requested" },
	{ 0x0024, 0x0102, "PidTagOriginatorReturnAddress",				"Originator return address" },
	{ 0x0025, 0x0102, "PidTagParentKey",						"Parent key" },
	{ 0x0026, 0x0003, "PidTagPriority",						"Priority" },
	{ 0x0027, 0x0102, "PidTagOriginCheck",						"Origin verification value" },
	{ 0x0028, 0x000b, "PidTagProofOfSubmissionRequested",				"ASN.1 proof of submission requested" },
	{ 0x0029, 0x000b, "PidTagReadReceiptRequested",					"Read receipt requested" },
	{ 0x002a, 0x0040, "PidTagReceiptTime",						"Receipt time" },
	{ 0x002b, 0x000b, "PidTagRecipientReassignmentProhibited",			"Recipient reassignment prohibited" },
	{ 0x002c, 0x0102, "PR_REDIRECTION_HISTORY",					"" },
	{ 0x002d, 0x0102, "PR_RELATED_IPMS",						"" },
	{ 0x002e, 0x0003, "PidTagOriginalSensitivity",					"Original sensitivity" },
	{ 0x002f, 0x001e, "PR_LANGUAGES",						"" },
	{ 0x0030, 0x0040, "PidTagReplyTime",						"Reply deadline" },
	{ 0x0031, 0x0102, "PidTagReportTag",						"Report tag" },
	{ 0x0032, 0x0040, "PR_REPORT_TIME",						"" },
	{ 0x0033, 0x000b, "PR_RETURNED_IPM",						"" },
	{ 0x0034, 0x0003, "PidTagSecurity",						"Security" },
	{ 0x0035, 0x000b, "PR_INCOMPLETE_COPY",						"" },
	{ 0x0036, 0x0003, "PidTagSensitivity",						"Sensitivity" },
	{ 0x0037, 0x001e, "PidTagSubject",						"Subject" },
	{ 0x0038, 0x0102, "PidTagSubjectMessageId",					"Subject message identifier" },
	{ 0x0039, 0x0040, "PidTagClientSubmitTime",					"Client submit time" },
	{ 0x003a, 0x001e, "PR_REPORT_NAME",						"" },
	{ 0x003b, 0x0102, "PidTagSentRepresentingSearchKey",				"Sent representing search key" },
	{ 0x003c, 0x0102, "PR_X400_CONTENT_TYPE",					"" },
	{ 0x003d, 0x001e, "PidTagSubjectPrefix",					"Subject prefix" },
	{ 0x003e, 0x0003, "PR_NON_RECEIPT_REASON",					"" },
	{ 0x003f, 0x0102, "PidTagReceivedByEntryId",					"Received by entry identifier" },
	{ 0x0040, 0x001e, "PidTagReceivedByName",					"Received by name" },
	{ 0x0041, 0x0102, "PidTagSentRepresentingEntryId",				"Sent representing entry identifier" },
	{ 0x0042, 0x001e, "PidTagSentRepresentingName",					"Sent representing name" },
	{ 0x0043, 0x0102, "PR_RCVD_REPRESENTING_ENTRYID",				"Received representing entry identifier" },
	{ 0x0044, 0x001e, "PR_RCVD_REPRESENTING_NAME",					"Received representing name" },
	{ 0x0045, 0x0102, "PR_REPORT_ENTRYID",						"Report entry identifier" },
	{ 0x0046, 0x0102, "PR_READ_RECEIPT_ENTRYID",					"Read receipt entry identifier" },
	{ 0x0047, 0x0102, "PR_MESSAGE_SUBMISSION_ID",					"" },
	{ 0x0048, 0x0040, "PR_PROVIDER_SUBMIT_TIME",					"" },
	{ 0x0049, 0x001e, "PidTagOriginalSubject",					"Original subject" },
	{ 0x004a, 0x000b, "PR_DISC_VAL",						"" },
	{ 0x004b, 0x001e, "PR_ORIG_MESSAGE_CLASS",					"" },
	{ 0x004c, 0x0102, "PidTagOriginalAuthorEntryId",				"Original author entry identifier" },
	{ 0x004d, 0x001e, "PidTagOriginalAuthorName",					"Original author name" },
	{ 0x004e, 0x0040, "PidTagOriginalSubmitTime",					"Original submit time" },
	{ 0x004f, 0x0102, "PR_REPLY_RECIPIENT_ENTRIES",					"Reply recipient entries" },
	{ 0x0050, 0x001e, "PidTagReplyRecipientEntries",				"Reply recipient names" },
	{ 0x0051, 0x0102, "PR_RECEIVED_BY_SEARCH_KEY",					"Received by search key" },
	{ 0x0052, 0x0102, "PR_RCVD_REPRESENTING_SEARCH_KEY",				"Received representing search key" },
	{ 0x0053, 0x0102, "PR_READ_RECEIPT_SEARCH_KEY",					"" },
	{ 0x0054, 0x0102, "PR_REPORT_SEARCH_KEY",					"" },
	{ 0x0055, 0x0040, "PR_ORIGINAL_DELIVERY_TIME",					"" },
	{ 0x0056, 0x0102, "PR_ORIGINAL_AUTHOR_SEARCH_KEY",				"" },
	{ 0x0057, 0x000b, "PidTagMessageToMe",						"My address in To field" },
	{ 0x0058, 0x000b, "PidTagMessageCcMe",						"My address in CC field" },
	{ 0x0059, 0x000b, "PidTagMessageRecipientMe",					"Message addressed to me" },
	{ 0x005a, 0x001e, "PidTagOriginalSenderName",					"Orginal sender name" },
	{ 0x005b, 0x0102, "PidTagOriginalSenderEntryId",				"Orginal sender entry identifier" },
	{ 0x005c, 0x0102, "PidTagOriginalSenderSearchKey",				"Original sender search key" },
	{ 0x005d, 0x001e, "PidTagOriginalSentRepresentingName",				"Original sent representing name" },
	{ 0x005e, 0x0102, "PidTagOriginalSentRepresentingEntryId",			"Original sent representing entry identifier" },
	{ 0x005f, 0x0102, "PidTagOriginalSentRepresentingSearchKey",			"Original sent representing search key" },
	{ 0x0060, 0x0040, "PidTagStartDate",						"Appointment start date and time" },
	{ 0x0061, 0x0040, "PidTagEndDate",						"Appointment end date and time" },
	{ 0x0062, 0x0003, "PidTagOwnerAppointmentId",					"Appointment owner identifier" },
	{ 0x0063, 0x000b, "PidTagResponseRequested",					"Response requested" },
	{ 0x0064, 0x001e, "PidTagSentRepresentingAddressType",				"Sent representing address type" },
	{ 0x0065, 0x001e, "PidTagSentRepresentingEmailAddress",				"Sent representing e-mail address" },
	{ 0x0066, 0x001e, "PidTagOriginalSenderAddressType",				"Original sender address type" },
	{ 0x0067, 0x001e, "PidTagOriginalSenderEmailAddress",				"Original sender e-mail address" },
	{ 0x0068, 0x001e, "PidTagOriginalSentRepresentingAddressType",			"Original sent representing address type" },
	{ 0x0069, 0x001e, "PidTagOriginalSentRepresentingEmailAddress",			"Original sent representing e-mail address" },
	{ 0x0070, 0x001e, "PidTagConversationTopic",					"Conversation topic" },
	{ 0x0071, 0x0102, "PidTagConversationIndex",					"Conversation index" },
	{ 0x0072, 0x001e, "PidTagOriginalDisplayBcc",					"Original display BCC" },
	{ 0x0073, 0x001e, "PidTagOriginalDisplayCc",					"Original display CC" },
	{ 0x0074, 0x001e, "PidTagOriginalDisplayTo",					"Original display To" },
	{ 0x0075, 0x001e, "PidTagReceivedByAddressType",				"Received by address type" },
	{ 0x0076, 0x001e, "PidTagReceivedByEmailAddress",				"Received by e-mail address" },
	{ 0x0077, 0x001e, "PidTagReceivedRepresentingAddressType",			"Received representing address type" },
	{ 0x0078, 0x001e, "PidTagReceivedRepresentingEmailAddress",			"Received representing e-mail address" },
	{ 0x0079, 0x001e, "PidTagOriginalAuthorAddressType",				"Original author address type" },
	{ 0x007a, 0x001e, "PidTagOriginalAuthorEmailAddress",				"Original author e-mail address" },
	{ 0x007b, 0x001e, "PidTagOriginallyIntendedRecipAddrtype",			"Originally intended recipient address type" },
	{ 0x007c, 0x001e, "PidTagOriginallyIntendedRecipEmailAddress",			"Originally intended recipient e-mail address" },
	{ 0x007d, 0x001e, "PidTagTransportMessageHeaders",				"Transport message headers" },
	{ 0x007e, 0x0102, "PidTagDelegation",						"Delegation" },
	{ 0x007f, 0x0102, "PidTagTnefCorrelationKey",					"TNEF correlation key" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The recipient property type (0x0c00 - 0x0dff)
 */
libfmapi_property_type_t libfmapi_recipient_property_types[ ] = {
	{ 0x0c00, 0x0102, "PR_CONTENT_INTEGRITY_CHECK",					"" },
	{ 0x0c01, 0x0003, "PR_EXPLICIT_CONVERSION",					"" },
	{ 0x0c02, 0x000b, "PidTagIpmReturnRequested",					"Return report requested" },
	{ 0x0c03, 0x0102, "PidTagMessageToken",						"Message ASN.1 secutiry token" },
	{ 0x0c04, 0x0003, "PR_NDR_REASON_CODE",						"" },
	{ 0x0c05, 0x0003, "PR_NDR_DIAG_CODE",						"" },
	{ 0x0c06, 0x000b, "PR_NON_RECEIPT_NOTIFICATION_REQUESTED",			"Non receipt notification requested" },
	{ 0x0c07, 0x0003, "PR_DELIVERY_POINT",						"" },
	{ 0x0c08, 0x000b, "PR_ORIGINATOR_NON_DELIVERY_REPORT_REQUESTED",		"Originator non delivery report requested" },
	{ 0x0c09, 0x0102, "PR_ORIGINATOR_REQUESTED_ALTERNATE_RECIPIENT",		"" },
	{ 0x0c0a, 0x000b, "PR_PHYSICAL_DELIVERY_BUREAU_FAX_DELIVERY",			"" },
	{ 0x0c0b, 0x0003, "PR_PHYSICAL_DELIVERY_MODE",					"" },
	{ 0x0c0c, 0x0003, "PR_PHYSICAL_DELIVERY_REPORT_REQUEST",			"" },
	{ 0x0c0d, 0x0102, "PR_PHYSICAL_FORWARDING_ADDRESS",				"" },
	{ 0x0c0e, 0x000b, "PR_PHYSICAL_FORWARDING_ADDRESS_REQUESTED",			"" },
	{ 0x0c0f, 0x000b, "PR_PHYSICAL_FORWARDING_PROHIBITED",				"" },
	{ 0x0c10, 0x0102, "PR_PHYSICAL_RENDITION_ATTRIBUTES",				"" },
	{ 0x0c11, 0x0102, "PR_PROOF_OF_DELIVERY",					"" },
	{ 0x0c12, 0x000b, "PR_PROOF_OF_DELIVERY_REQUESTED",				"" },
	{ 0x0c13, 0x0102, "PidTagRecipientCertificate",					"Recipient certificate" },
	{ 0x0c14, 0x001e, "PR_RECIPIENT_NUMBER_FOR_ADVICE",				"" },
	{ 0x0c15, 0x0003, "PidTagRecipientType",					"Recipient type" },
	{ 0x0c16, 0x0003, "PR_REGISTERED_MAIL_TYPE",					"" },
	{ 0x0c17, 0x000b, "PR_REPLY_REQUESTED",						"" },
	{ 0x0c18, 0x0003, "PR_REQUESTED_DELIVERY_METHOD",				"" },
	{ 0x0c19, 0x0102, "PidTagSenderEntryId",					"Sender entry identifier" },
	{ 0x0c1a, 0x001e, "PidTagSenderName",						"Sender entry name" },
	{ 0x0c1b, 0x001e, "PR_SUPPLEMENTARY_INFO",					"" },
	{ 0x0c1c, 0x0003, "PR_TYPE_OF_MTS_USER",					"" },
	{ 0x0c1d, 0x0102, "PidTagSenderSearchKey",					"Sender search key" },
	{ 0x0c1e, 0x001e, "PidTagSenderAddressType",					"Sender address type" },
	{ 0x0c1f, 0x001e, "PidTagSenderEmailAddress",					"Sender e-mail address" },
	{ 0x0c20, 0x0003, "PR_NDR_STATUS_CODE",						"None delivery status code" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The non-transmittable message property type (0x0e00 - 0x0fff)
 */
libfmapi_property_type_t libfmapi_non_transmittable_message_property_types[ ] = {
	{ 0x0e00, 0x0014, "PidTagCurrentVersion",					"Message store verion" },
	{ 0x0e01, 0x000b, "PidTagDeleteAfterSubmit",					"Delete after submit" },
	{ 0x0e02, 0x001e, "PidTagDisplayBcc",						"Display BCC" },
	{ 0x0e03, 0x001e, "PidTagDisplayCc",						"Display CC" },
	{ 0x0e04, 0x001e, "PidTagDisplayTo",						"Display To" },
	{ 0x0e05, 0x001e, "PidTagParentDisplay",					"Parent display name" },
	{ 0x0e06, 0x0040, "PidTagOriginalDeliveryTime",					"Message delivery time" },
	{ 0x0e07, 0x0003, "PidTagMessageFlags",						"Message flags" },
	{ 0x0e08, 0x0003, "PidTagMessageSize",						"Message size (32-bit)" },
	{ 0x0e08, 0x0014, "PidTagMessageSizeExtended",					"Message size (64-bit)" },
	{ 0x0e09, 0x0102, "PidTagParentEntryId",					"Parent folder entry identifier" },
	{ 0x0e0a, 0x0102, "PidTagSentMailEntryId",					"Sent mail folder entry identifier" },
	{ 0x0e0c, 0x000b, "PidTagCorrelate",						"Correlation requested" },
	{ 0x0e0d, 0x0102, "PidTagCorrelateMtsid",					"Correlation  message transfer system identifier" },
	{ 0x0e0e, 0x000b, "PidTagDiscreteValues",					"Report applies to specific members only" },
	{ 0x0e0f, 0x000b, "PidTagResponsibility",					"Transport provider has responsibility" },
	{ 0x0e10, 0x0003, "PidTagSpoolerStatus",					"Spooler status" },
	{ 0x0e11, 0x0003, "PR_TRANSPORT_STATUS",					"" },
	{ 0x0e12, 0x000d, "PR_MESSAGE_RECIPIENTS",					"" },
	{ 0x0e13, 0x000d, "PR_MESSAGE_ATTACHMENTS",					"" },
	{ 0x0e14, 0x0003, "PidTagSubmitFlags",						"Message submit flags" },
	{ 0x0e15, 0x0003, "PR_RECIPIENT_STATUS",					"" },
	{ 0x0e16, 0x0003, "PR_TRANSPORT_KEY",						"" },
	{ 0x0e17, 0x0003, "PidTagMessageStatus",					"Message status flags" },
	{ 0x0e18, 0x0003, "PR_MESSAGE_DOWNLOAD_TIME",					"" },
	{ 0x0e19, 0x0014, "PR_CREATION_VERSION",					"" },
	{ 0x0e1a, 0x0014, "PR_MODIFY_VERSION",						"" },
	{ 0x0e1b, 0x000b, "PR_HASATTACH",						"" },
	{ 0x0e1c, 0x0003, "PidTagBodyCrc",						"Plain text message body checksum" },
	{ 0x0e1d, 0x001e, "PidTagNormalizedSubject",					"Normalized subject" },
	{ 0x0e1f, 0x000b, "PidTagRtfInSync",						"Compressed RTF message body in sync with plain text" },
	{ 0x0e20, 0x0003, "PidTagAttachSize",						"Attachment size" },
	{ 0x0e21, 0x0003, "PidTagAttachNumber",						"Attachment number" },
	{ 0x0e22, 0x000b, "PidTagPreprocess",						"Needs preprocessing" },
	{ 0x0e23, 0x0003, "PidTagInternetArticleNumber",				"Internet article number" },
	{ 0x0e24, 0x001e, "PR_NEWSGROUP_NAME",						"" },
	{ 0x0e25, 0x0102, "PR_ORIGINATING_MTA_CERTIFICATE",				"" },
	{ 0x0e26, 0x0102, "PR_PROOF_OF_SUBMISSION",					"" },
	{ 0x0e27, 0x0102, "PidTagSecurityDescriptor",					"Permissions (NT security descriptor)" },
	{ 0x0e28, 0x001e, "PR_PRIMARY_SEND_ACCT",					"Primary send account identifier" },
	{ 0x0e29, 0x001e, "PR_NEXT_SEND_ACCT",						"Secondary send account identifier" },

	{ 0x0e30, 0x0003, "PidTagReplItemid",						"Replication item identifier" },
	{ 0x0e30, 0x0102, "PidTagReplItemid",						"Replication item identifier" },

	{ 0x0e33, 0x0014, "PidTagReplChangenum",					"Replication change number" },
	{ 0x0e34, 0x0102, "PidTagReplVersionHistory",					"Replication version history" },
	{ 0x0e38, 0x0003, "PidTagReplFlags",						"Replication flags" },
	{ 0x0e3c, 0x0102, "PidTagReplCopiedfromVersionhistory",				"Replication version information" },
	{ 0x0e3d, 0x0102, "PidTagReplCopiedfromItemid",					"Replication item identifier information" },

	{ 0x0e58, 0x0102, "PR_CREATOR_SID",						"Creator (NT security identifier)" },
	{ 0x0e59, 0x0102, "PR_LAST_MODIFIER_SID",					"Last modifier (NT security identifier)" },
	{ 0x0e5e, 0x0048, "PR_MIME_HANDLER_CLASSID",					"MIME handle class identifier" },
	{ 0x0e5e, 0x1048, "PR_MIME_HANDLER_CLASSIDS",					"MIME handle class identifiers" },
	{ 0x0e61, 0x0003, "PR_URL_COMP_NAME_POSTFIX",					"URL computer name postfix" },
	{ 0x0e62, 0x000b, "PR_URL_COMP_NAME_SET",					"URL computer name set" },
	{ 0x0e63, 0x0003, "PR_SUBFOLDER_CT",						"" },
	{ 0x0e64, 0x0003, "PR_DELETED_SUBFOLDER_CT",					"" },
	{ 0x0e66, 0x0040, "PR_DELETE_TIME",						"" },
	{ 0x0e67, 0x0102, "PR_AGE_LIMIT",						"" },
	{ 0x0e79, 0x0003, "PR_TRUST_SENDER",						"Trust sender" },
	{ 0x0e96, 0x0102, "PR_ATTACH_VIRUS_SCAN_INFO",					"" },

	{ 0x0ea0, 0x0048, "PR_ASSOCIATED_SHARING_PROVIDER",				"Associated sharing provider identifier" },

	{ 0x0ea3, 0x0102, "PidTagProviderItemId",					"Provider identifier" },
	{ 0x0ea4, 0x0102, "PidTagProviderParentItemId",					"Parent provider identifier" },

	{ 0x0ff4, 0x0003, "PidTagAccess",						"Client access flags" },
	{ 0x0ff5, 0x0102, "PidTagRowType",						"Row type" },
	{ 0x0ff6, 0x0003, "PidTagInstanceKey",						"Instance key" },
	{ 0x0ff7, 0x0003, "PidTagAccessLevel",						"Client access level flags" },
	{ 0x0ff8, 0x0102, "PidTagMappingSignature",					"Mapping signature" },
	{ 0x0ff9, 0x0102, "PidTagRecordKey",						"Record key" },
	{ 0x0ffa, 0x0102, "PidTagStoreRecordKey",					"Message store record key" },
	{ 0x0ffb, 0x0102, "PidTagStoreEntryId",						"Message store entry identifier" },
	{ 0x0ffc, 0x0102, "PidTagMiniIcon",						"Mini icon bitmap" },
	{ 0x0ffd, 0x0102, "PidTagIcon",							"Icon bitmap" },
	{ 0x0ffe, 0x0003, "PidTagObjectType",						"Object type" },
	{ 0x0fff, 0x0102, "PidTagEntryId",						"Entry identifier" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The message content property type (0x1000 - 0x2fff)
 */
libfmapi_property_type_t libfmapi_message_content_property_types[ ] = {
	{ 0x1000, 0x001e, "PidTagBody",							"Plain text message body" },
	{ 0x1001, 0x001e, "PidTagReportText",						"Report text" },
	{ 0x1002, 0x0102, "PidTagOriginatorAndDistributionListExpansionHistory",	"Originator and distribution list expansion history" },
	{ 0x1003, 0x0102, "PR_REPORTING_DL_NAME",					"" },
	{ 0x1004, 0x0102, "PR_REPORTING_MTA_CERTIFICATE",				"" },
	{ 0x1006, 0x0003, "PR_RTF_SYNC_BODY_CRC",					"" },
	{ 0x1007, 0x0003, "PR_RTF_SYNC_BODY_COUNT",					"" },
	{ 0x1008, 0x001e, "PR_RTF_SYNC_BODY_TAG",					"" },
	{ 0x1009, 0x0102, "PidTagRtfCompressed",					"Compressed RTF message body" },
	{ 0x1010, 0x0003, "PR_RTF_SYNC_PREFIX_COUNT",					"" },
	{ 0x1011, 0x0003, "PR_RTF_SYNC_TRAILING_COUNT",					"" },
	{ 0x1012, 0x0102, "PR_ORIGINALLY_INTENDED_RECIP_ENTRYID",			"" },
	{ 0x1013, 0x001e, "PidTagBodyHtml",						"HTML message body" },
	{ 0x1013, 0x0102, "PidTagHtml",							"HTML message body" },
	{ 0x1014, 0x001e, "PidTagBodyContentLocation",					"Message body content location" },

	{ 0x1030, 0x001e, "PR_INTERNET_APPROVED",					"" },
	{ 0x1031, 0x001e, "PR_INTERNET_CONTROL",					"" },
	{ 0x1032, 0x001e, "PR_INTERNET_DISTRIBUTION",					"" },
	{ 0x1033, 0x001e, "PR_INTERNET_FOLLOWUP_TO",					"" },
	{ 0x1034, 0x0003, "PR_INTERNET_LINES",						"" },
	{ 0x1035, 0x001e, "PidTagInternetMessageId",					"Message identifier" },
	{ 0x1036, 0x001e, "PR_INTERNET_NEWSGROUPS",					"" },
	{ 0x1037, 0x001e, "PR_INTERNET_ORGANIZATION",					"" },
	{ 0x1038, 0x001e, "PR_INTERNET_NNTP_PATH",					"" },
	{ 0x1039, 0x001e, "PR_INTERNET_REFERENCES",					"" },
	{ 0x103a, 0x001e, "PR_SUPERSEDES",						"" },
	{ 0x103b, 0x0102, "PR_POST_FOLDER_ENTRIES",					"" },
	{ 0x103c, 0x001e, "PR_POST_FOLDER_NAMES",					"" },
	{ 0x103d, 0x0102, "PR_POST_REPLY_FOLDER_ENTRIES",				"" },
	{ 0x103e, 0x001e, "PR_POST_REPLY_FOLDER_NAMES",					"" },
	{ 0x103f, 0x0102, "PR_POST_REPLY_DENIED",					"" },
	{ 0x1040, 0x001e, "PR_NNTP_XREF",						"" },
	{ 0x1041, 0x001e, "PR_INTERNET_PRECEDENCE",					"" },
	{ 0x1042, 0x001e, "PR_IN_REPLY_TO_ID",						"" },
	{ 0x1043, 0x001e, "PR_LIST_HELP",						"" },
	{ 0x1044, 0x001e, "PR_LIST_SUBSCRIBE",						"" },
	{ 0x1045, 0x001e, "PR_LIST_UNSUBSCRIBE",					"" },
	{ 0x1046, 0x001e, "PidTagInternetReturnPath",					"Internet return path" },
	{ 0x1080, 0x0003, "PidTagIconIndex",						"Icon index" },
	{ 0x1081, 0x0003, "PR_ACTION_FLAG",						"" },
	{ 0x1082, 0x0040, "PR_ACTION_DATE",						"" },
	{ 0x1090, 0x0003, "PidTagFlagStatus",						"Flag status" },
	{ 0x1091, 0x0040, "PR_FLAG_COMPLETE",						"" },

	{ 0x1095, 0x0003, "PR_FLAG_ICON",						"Flag icon index" },
	{ 0x1096, 0x0003, "PidTagBlockStatus",						"Block status" },
	{ 0x1097, 0x0003, "PidTagItemTemporaryFlags",					"Temporary item flags" },
	{ 0x1098, 0x1102, "PidTagConflictItems",					"Conflict items" },

	{ 0x10c0, 0x0102, "PR_SMTP_TEMP_TBL_DATA",					"" },
	{ 0x10c1, 0x0003, "PR_SMTP_TEMP_TBL_DATA_2",					"" },
	{ 0x10c2, 0x0102, "PR_SMTP_TEMP_TBL_DATA_3",					"" },
	{ 0x10c3, 0x0040, "PR_CAL_START_TIME",						"" },
	{ 0x10c4, 0x0040, "PR_CAL_END_TIME",						"" },
	{ 0x10c5, 0x0040, "PR_CAL_RECURRING_ID",					"" },
	{ 0x10c6, 0x001e, "PR_DAV_SUBMIT_DATA",						"" },
	{ 0x10c7, 0x0003, "PR_CDO_EXPANSION_INDEX",					"" },
	{ 0x10c8, 0x0102, "PR_IFS_INTERNAL_DATA",					"" },
	{ 0x10ca, 0x0040, "PR_CAL_REMINDER_NEXT_TIME",					"" },
	{ 0x10f1, 0x001e, "PR_OWA_URL",							"" },
	{ 0x10f2, 0x000b, "PR_DISABLE_FULL_FIDELITY",					"Disable full fidelity" },
	{ 0x10f3, 0x001e, "PidTagUrlComponentName",					"URL computer name" },
	{ 0x10f4, 0x000b, "PidTagAttributeHidden",					"Attribute hidden" },
	{ 0x10f5, 0x000b, "PidTagAttributeSystem",					"Attribute system" },
	{ 0x10f6, 0x000b, "PidTagAttributeReadOnly",					"Attribute read only" },
	{ 0x1100, 0x0102, "PR_P1_CONTENT",						"" },
	{ 0x1101, 0x0102, "PR_P1_CONTENT_TYPE",						"" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The common object property type (0x3000 - 0x32ff)
 */
libfmapi_property_type_t libfmapi_common_object_property_types[ ] = {
	{ 0x3000, 0x0003, "PidTagRowid",						"Recipient row identifier" },
	{ 0x3001, 0x001e, "PidTagDisplayName",						"Message store display name" },
	{ 0x3002, 0x001e, "PidTagAddressType",						"E-mail address type" },
	{ 0x3003, 0x001e, "PidTagEmailAddress",						"E-mail address" },
	{ 0x3004, 0x001e, "PidTagComment",						"Comment" },
	{ 0x3005, 0x0003, "PidTagDepth",						"Hierarchy table depth" },
	{ 0x3006, 0x001e, "PidTagProviderDisplayName",					"Service provider display name" },
	{ 0x3007, 0x0040, "PidTagCreationTime",						"Creation time" },
	{ 0x3008, 0x0040, "PidTagLastModificationTime",					"Last modification time" },
	{ 0x3009, 0x0003, "PidTagResourceFlags",					"Resource flags" },
	{ 0x300a, 0x001e, "PidTagProviderDisplay",					"Service provider DLL filename" },
	{ 0x300b, 0x0102, "PidTagSearchKey",						"Search key" },
	{ 0x300c, 0x0102, "PidTagProviderUid",						"Service provider identifier" },
	{ 0x300d, 0x0003, "PidTagProviderOrdinal",					"Service provider table index" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The form property type (0x3300 - 0x33ff)
 */
libfmapi_property_type_t libfmapi_form_property_types[ ] = {
	{ 0x3301, 0x001e, "PR_FORM_VERSION",						"" },
	{ 0x3302, 0x0048, "PR_FORM_CLSID",						"" },
	{ 0x3303, 0x001e, "PR_FORM_CONTACT_NAME",					"" },
	{ 0x3304, 0x001e, "PR_FORM_CATEGORY",						"" },
	{ 0x3305, 0x001e, "PR_FORM_CATEGORY_SUB",					"" },
	{ 0x3306, 0x1003, "PR_FORM_HOST_MAP",						"" },
	{ 0x3307, 0x000b, "PR_FORM_HIDDEN",						"" },
	{ 0x3308, 0x001e, "PR_FORM_DESIGNER_NAME",					"" },
	{ 0x3309, 0x0048, "PR_FORM_DESIGNER_GUID",					"" },
	{ 0x330a, 0x0003, "PR_FORM_MESSAGE_BEHAVIOR",					"" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The message store property type (0x3400 - 0x35ff)
 */
libfmapi_property_type_t libfmapi_message_store_property_types[ ] = {
	{ 0x3400, 0x000b, "PR_DEFAULT_STORE",						"" },
	{ 0x340d, 0x0003, "PidTagStoreSupportMask",					"Message store characteristics mask" },
	{ 0x340e, 0x0003, "PR_STORE_STATE",						"" },
	{ 0x3410, 0x0102, "PR_IPM_SUBTREE_SEARCH_KEY",					"" },
	{ 0x3411, 0x0102, "PR_IPM_OUTBOX_SEARCH_KEY",					"" },
	{ 0x3412, 0x0102, "PR_IPM_WASTEBASKET_SEARCH_KEY",				"" },
	{ 0x3413, 0x0102, "PR_IPM_SENTMAIL_SEARCH_KEY",					"" },
	{ 0x3414, 0x0102, "PidTagStoreProvider",					"Message store provider" },
	{ 0x3415, 0x000d, "PR_RECEIVE_FOLDER_SETTINGS",					"" },
	{ 0x3416, 0x0102, "",								"Item proc search entry identifier" },
	{ 0x3419, 0x0003, "PR_SEARCH_OWNER_ID",						"Search owner identifier" },

	{ 0x35df, 0x0003, "PidTagValidFolderMask",					"Valid folder mask" },
	{ 0x35e0, 0x0102, "PidTagIpmSubtreeEntryId",					"IPM sub tree root folder entry identifier" },
	{ 0x35e2, 0x0102, "PidTagIpmOutboxEntryId",					"Outbox folder entry identifier" },
	{ 0x35e3, 0x0102, "PidTagIpmWastebasketEntryId",				"Wastebasket folder entry identifier" },
	{ 0x35e4, 0x0102, "PidTagIpmSentMailEntryId",					"Sent mail folder entry identifier" },
	{ 0x35e5, 0x0102, "PidTagViewsEntryId",						"Views folder entry identifier" },
	{ 0x35e6, 0x0102, "PidTagCommonViewsEntryId",					"Common views folder entry identifier" },
	{ 0x35e7, 0x0102, "PidTagFinderEntryId",					"Finder folder entry identifier" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The folder and address book property type (0x3600 - 0x36ff)
 */
libfmapi_property_type_t libfmapi_folder_and_address_book_property_types[ ] = {
	{ 0x3600, 0x0003, "PidTagContainerFlags",					"Address book container capabilities flags" },
	{ 0x3601, 0x0003, "PidTagFolderType",						"Folder type" },
	{ 0x3602, 0x0003, "PidTagContentCount",						"Number of content items" },
	{ 0x3603, 0x0003, "PidTagContentUnreadCount",					"Number of unread content items" },
	{ 0x3604, 0x000d, "PidTagCreateTemplates",					"Dialog box template entry identifiers" },
	{ 0x3605, 0x000d, "PidTagDetailsTable",						"Display table object" },

	{ 0x3607, 0x000d, "PR_SEARCH",							"Advanced search object" },
	{ 0x3609, 0x000b, "PR_SELECTABLE",						"Table entry selectable" },
	{ 0x360a, 0x000b, "PidTagSubfolders",						"Has sub folders" },
	{ 0x360b, 0x0003, "PR_STATUS",							"Folder status flags" },
	{ 0x360c, 0x001e, "PR_ANR",							"Address book property restriction" },
	{ 0x360d, 0x1003, "PR_CONTENTS_SORT_ORDER",					"Content item sort order" },
	{ 0x360e, 0x000d, "PR_CONTAINER_HIERARCHY",					"Hierarchy table" },
	{ 0x360f, 0x000d, "PR_CONTAINER_CONTENTS",					"Contents table" },
	{ 0x3610, 0x000d, "PR_FOLDER_ASSOCIATED_CONTENTS",				"Associated contents table" },
	{ 0x3611, 0x0102, "PR_DEF_CREATE_DL",						"Distribution list template identifier" },
	{ 0x3612, 0x0102, "PR_DEF_CREATE_MAILUSER",					"Messaging user template identifier" },
	{ 0x3613, 0x001e, "PidTagContainerClass",					"Container class" },
	{ 0x3614, 0x0014, "PR_CONTAINER_MODIFY_VERSION",				"Current modification version" },
	{ 0x3615, 0x0102, "PidTagAbProviderId",						"Address book provider" },
	{ 0x3616, 0x0102, "PidTagDefaultViewEntryId",					"Default view entry identifier" },
	{ 0x3617, 0x0003, "PidTagAssociatedContentCount",				"Number of associated content items" },
	{ 0x361c, 0x0102, "PR_PACKED_NAME_PROPS",					"" },

	{ 0x36d0, 0x0102, "PidTagIpmAppointmentEntryId",				"Calendar folder entry identifier" },
	{ 0x36d1, 0x0102, "PidTagIpmContactEntryId",					"Contact folder entry identifier" },
	{ 0x36d2, 0x0102, "PidTagIpmJournalEntryId",					"Journal folder entry identifier" },
	{ 0x36d3, 0x0102, "PidTagIpmNoteEntryId",					"Notes folder entry identifier" },
	{ 0x36d4, 0x0102, "PidTagIpmTaskEntryId",					"Tasks folder entry identifier" },
	{ 0x36d5, 0x0102, "PidTagRemindersOnlineEntryId",				"Online reminders folder entry identifier" },
	{ 0x36d6, 0x0102, "PR_REMINDERS_OFFLINE_ENTRYID",				"Offline reminders folder entry identifier" },
	{ 0x36d7, 0x0102, "PidTagIpmDraftsEntryId",					"Drafts entry identifier" },
	{ 0x36d8, 0x1102, "PidTagAdditionalRenEntryIds",				"Additional REN folder entry identifiers" },
	{ 0x36d9, 0x0102, "PidTagAdditionalRenEntryIdsEx",				"Additional REN folder entry identifiers" },
	{ 0x36da, 0x0102, "PidTagExtendedFolderFlags",					"Extended folder flags" },

	{ 0x36df, 0x0102, "PidTagFolderWebViewInfo",					"Folder web view information" },

	{ 0x36e0, 0x0102, "PR_FOLDER_XVIEWINFO_E",					"" },
	{ 0x36e1, 0x0003, "PR_FOLDER_VIEWS_ONLY",					"" },
	{ 0x36e2, 0x0003, "PidTagOrdinalMost",						"Task ordinal maximum" },

	{ 0x36e4, 0x1102, "PidTagFreeBusyEntryIds",					"Free busy entry identifiers" },
	{ 0x36e5, 0x001e, "PR_DEF_MSG_CLASS",						"" },
	{ 0x36e6, 0x001e, "PR_DEF_FORM_NAME",						"" },
	{ 0x36e9, 0x000b, "PR_GENERATE_EXCHANGE_VIEWS",					"" },
	{ 0x36eb, 0x0102, "PR_FOLDER_VIEWLIST",						"Folder view list" },
	{ 0x36ec, 0x0003, "PR_AGING_PERIOD",						"Aging period" },
	{ 0x36ee, 0x0003, "PR_AGING_GRANULARITY",					"Aging period granularity" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The attachment property type (0x3700 - 0x38ff)
 */
libfmapi_property_type_t libfmapi_attachment_property_types[ ] = {
	{ 0x3700, 0x0102, "PR_ATTACHMENT_X400_PARAMETERS",				"Attachment transmission parameters" },
	{ 0x3701, 0x000d, "PidTagAttachDataObject",					"Attachment object" },
	{ 0x3701, 0x0102, "PidTagAttachDataBinary",					"Attachment binary data" },
	{ 0x3702, 0x0102, "PidTagAttachEncoding",					"Attachment encoding" },
	{ 0x3703, 0x001e, "PidTagAttachExtension",					"Attachment extension" },
	{ 0x3704, 0x001e, "PidTagAttachFilename",					"Attachment (short) filename" },
	{ 0x3705, 0x0003, "PidTagAttachMethod",						"Attachment method" },

	{ 0x3707, 0x001e, "PidTagAttachLongFilename",					"Attachment long filename" },
	{ 0x3708, 0x001e, "PidTagAttachPathname",					"Attachment (short) pathname" },
	{ 0x3709, 0x0102, "PidTagAttachRendering",					"Attachment rendering information" },
	{ 0x370a, 0x0102, "PidTagAttachTag",						"Attachment application tag" },
	{ 0x370b, 0x0003, "PidTagRenderingPosition",					"Attachment rendering offset" },
	{ 0x370c, 0x001e, "PidTagAttachTransportName",					"Attachment TNEF transport name" },
	{ 0x370d, 0x001e, "PidTagAttachLongPathname",					"Attachment long pathname" },
	{ 0x370e, 0x001e, "PidTagAttachMimeTag",					"Attachment MIME type" },
	{ 0x370f, 0x0102, "PidTagAttachAdditionalInformation",				"Attachment encoding information" },
	{ 0x3710, 0x0003, "PidTagAttachMimeSequence",					"Attachment MIME sequence number" },
	{ 0x3711, 0x001e, "PidTagAttachContentBase",					"Attachment MIME content base header URI" },
	{ 0x3712, 0x001e, "PidTagAttachContentId",					"Attachment MIME content identifier header" },
	{ 0x3713, 0x001e, "PidTagAttachContentLocation",				"Attachment MIME content location header" },
	{ 0x3714, 0x0003, "PidTagAttachFlags",						"Attachment flags" },

	{ 0x3716, 0x001e, "PR_ATTACH_CONTENT_DISPOSITION",				"" },

	{ 0x3719, 0x001e, "PidTagAttachPayloadProviderGuidString",			"Attachment MIME X-Payload-Provider-Guid header" },
	{ 0x371a, 0x001e, "PidTagAttachPayloadClass",					"Attachment MIME X-Payload-Class header" },
	{ 0x371b, 0x001e, "PidTagTextAttachmentCharset",				"Attachment character set" },

	{ 0x3880, 0x0102, "PR_SYNCEVENT_SUPPRESS_GUID",					"" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The address book property type (0x3900 - 0x39ff)
 */
libfmapi_property_type_t libfmapi_address_book_property_types[ ] = {
	{ 0x3900, 0x0003, "PidTagDisplayType",						"Icon display type" },
	{ 0x3902, 0x0102, "PidTagTemplateid",						"Service provider template entry identifier" },
	{ 0x3904, 0x0102, "PidTagPrimaryCapability",					"Primary capability" },
	{ 0x3905, 0x0003, "PidTagDisplayTypeEx",					"Extended icon display type" },
	{ 0x39fe, 0x001e, "PidTagSmtpAddress",						"SMTP address" },
	{ 0x39ff, 0x001e, "PidTag7BitDisplayName",					"Messaging username" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The messaging user property type (0x3a00 - 0x3bff)
 */
libfmapi_property_type_t libfmapi_messaging_user_property_types[ ] = {
	{ 0x3a00, 0x001e, "PidTagAccount",						"Recipient account name" },
	{ 0x3a01, 0x0102, "PidTagAlternateRecipient",					"Alternate recipient entry identifiers" },
	{ 0x3a02, 0x001e, "PidTagCallbackTelephoneNumber",				"Callback telephone number" },
	{ 0x3a03, 0x000b, "PidTagConversionProhibited",					"Conversation prohibited" },
	{ 0x3a04, 0x000b, "PR_DISCLOSE_RECIPIENTS",					"Disclose recipient" },
	{ 0x3a05, 0x001e, "PidTagGeneration",						"Generational abbreviation" },
	{ 0x3a06, 0x001e, "PidTagGivenName",						"Given name" },
	{ 0x3a07, 0x001e, "PidTagGovernmentIdNumber",					"Government identifier" },
	{ 0x3a08, 0x001e, "PidTagBusinessTelephoneNumber",				"Business (office) phone number" },
	{ 0x3a09, 0x001e, "PidTagHomeTelephoneNumber",					"Home phone number" },
	{ 0x3a0a, 0x001e, "PidTagInitials",						"Initials" },
	{ 0x3a0b, 0x001e, "PidTagKeyword",						"Recipient identification keyword" },
	{ 0x3a0c, 0x001e, "PidTagLanguage",						"Language" },
	{ 0x3a0d, 0x001e, "PidTagLocation",						"Location" },
	{ 0x3a0e, 0x000b, "PidTagMailPermission",					"Permitted to send/receive messaged" },
	{ 0x3a0f, 0x001e, "PidTagMessageHandlingSystemCommonName",			"Message handling system (MHS) common name" },
	{ 0x3a10, 0x001e, "PidTagOrganizationalIdNumber",				"Organizational identification number" },
	{ 0x3a11, 0x001e, "PidTagSurname",						"Surname" },
	{ 0x3a12, 0x0102, "PidTagOriginalEntryId",					"Original entry identifier" },
	{ 0x3a13, 0x001e, "PidTagOriginalDisplayName",					"Original display name" },
	{ 0x3a14, 0x0102, "PidTagOriginalSearchKey",					"Original search key" },
	{ 0x3a15, 0x001e, "PidTagPostalAddress",					"Postal address" },
	{ 0x3a16, 0x001e, "PidTagCompanyName",						"Company name" },
	{ 0x3a17, 0x001e, "PidTagTitle",						"Job title" },
	{ 0x3a18, 0x001e, "PidTagDepartmentName",					"Department name" },
	{ 0x3a19, 0x001e, "PidTagOfficeLocation",					"Office location" },
	{ 0x3a1a, 0x001e, "PidTagPrimaryTelephoneNumber",				"Primary phone number" },
	{ 0x3a1b, 0x001e, "PidTagBusiness2TelephoneNumber",				"Secondary business (office) phone number" },
	{ 0x3a1c, 0x001e, "PidTagMobileTelephoneNumber",				"Mobile phone number" },
	{ 0x3a1d, 0x001e, "PidTagRadioTelephoneNumber",					"Radio phone number" },
	{ 0x3a1e, 0x001e, "PidTagCarTelephoneNumber",					"Car phone number" },
	{ 0x3a1f, 0x001e, "PidTagOtherTelephoneNumber",					"Alternate telephone number" },
	{ 0x3a20, 0x001e, "PidTagTransmittableDisplayName",				"Transmittable display name" },
	{ 0x3a21, 0x001e, "PidTagPagerTelephoneNumber",					"Pager phone number" },
	{ 0x3a22, 0x0102, "PidTagUserCertificate",					"User certificate" },
	{ 0x3a23, 0x001e, "PidTagPrimaryFaxNumber",					"Primary fax number" },
	{ 0x3a24, 0x001e, "PidTagBusinessFaxNumber",					"Business (office) fax number" },
	{ 0x3a25, 0x001e, "PidTagHomeFaxNumber",					"Home fax number" },
	{ 0x3a26, 0x001e, "PidTagCountry",						"Country" },
	{ 0x3a27, 0x001e, "PidTagLocality",						"Locality (town or city)" },
	{ 0x3a28, 0x001e, "PidTagStateOrProvince",					"State or province" },
	{ 0x3a29, 0x001e, "PidTagStreetAddress",					"Street" },
	{ 0x3a2a, 0x001e, "PidTagPostalCode",						"Postal code" },
	{ 0x3a2b, 0x001e, "PidTagPostOfficeBox",					"Post office box" },
	{ 0x3a2c, 0x001e, "PidTagTelexNumber",						"Telex number" },
	{ 0x3a2d, 0x001e, "PidTagIsdnNumber",						"ISDN number" },
	{ 0x3a2e, 0x001e, "PidTagAssistantTelephoneNumber",				"Assistant phone number" },
	{ 0x3a2f, 0x001e, "PidTagHome2TelephoneNumber",					"Secondary home phone number" },
	{ 0x3a30, 0x001e, "PidTagAssistant",						"Assistant name" },

	{ 0x3a40, 0x000b, "PidTagSendRichInfo",						"Can receive rich text (RTF, OLE)" },
	{ 0x3a41, 0x0040, "PidTagWeddingAnniversary",					"Wedding anniversary" },
	{ 0x3a42, 0x0040, "PidTagBirthday",						"Brithday" },
	{ 0x3a43, 0x001e, "PidTagHobbies",						"Hobbies" },
	{ 0x3a44, 0x001e, "PidTagMiddleName",						"Middle name(s)" },
	{ 0x3a45, 0x001e, "PidTagDisplayNamePrefix",					"Display name prefix" },
	{ 0x3a46, 0x001e, "PidTagProfession",						"Profession" },
	{ 0x3a47, 0x001e, "PidTagPreferredByName",					"Preferred name" },
	{ 0x3a48, 0x001e, "PidTagSpouseName",						"Name spouse" },
	{ 0x3a49, 0x001e, "PidTagComputerNetworkName",					"Computer network name" },
	{ 0x3a4a, 0x001e, "PidTagCustomerId",						"Customer identifier" },
	{ 0x3a4b, 0x001e, "PidTagTtyTddPhoneNumber",					"Text telephone (TTY) or telecommunication device for the deaf (TDD) phone number" },
	{ 0x3a4c, 0x001e, "PidTagFtpSite",						"FTP site" },
	{ 0x3a4d, 0x0002, "PidTagGender",						"Gender" },
	{ 0x3a4e, 0x001e, "PidTagManagerName",						"Name manager" },
	{ 0x3a4f, 0x001e, "PidTagNickname",						"Nickname" },
	{ 0x3a50, 0x001e, "PidTagPersonalHomePage",					"Personal home page" },
	{ 0x3a51, 0x001e, "PidTagBusinessHomePage",					"Business home page" },
	{ 0x3a52, 0x0048, "PidTagContactVersion",					"Contact version" },
	{ 0x3a53, 0x1102, "PR_CONTACT_ENTRYIDS",					"Contact entry identifiers" },
	{ 0x3a54, 0x101e, "PidTagContactAddressTypes",					"Contact address types" },
	{ 0x3a55, 0x0003, "PR_CONTACT_DEFAULT_ADDRESS_INDEX",				"Contact default address index" },
	{ 0x3a56, 0x101e, "PR_CONTACT_EMAIL_ADDRESSES",					"Contact email addresses" },
	{ 0x3a57, 0x001e, "PidTagCompanyMainTelephoneNumber",				"Company main phone number" },
	{ 0x3a58, 0x101e, "PidTagChildrensNames",					"Name(s) of children" },
	{ 0x3a59, 0x001e, "PidTagHomeAddressCity",					"City of home address" },
	{ 0x3a5a, 0x001e, "PidTagHomeAddressCountry",					"Country of home address" },
	{ 0x3a5b, 0x001e, "PidTagHomeAddressPostalCode",				"Postal code of home address" },
	{ 0x3a5c, 0x001e, "PidTagHomeAddressStateOrProvince",				"State or province of home address" },
	{ 0x3a5d, 0x001e, "PidTagHomeAddressStreet",					"Street of home address" },
	{ 0x3a5e, 0x001e, "PidTagHomeAddressPostOfficeBox",				"Post office box of home address" },
	{ 0x3a5f, 0x001e, "PidTagOtherAddressCity",					"City of other address" },
	{ 0x3a60, 0x001e, "PidTagOtherAddressCountry",					"Country of other address" },
	{ 0x3a61, 0x001e, "PidTagOtherAddressPostalCode",				"Postal code of other address" },
	{ 0x3a62, 0x001e, "PidTagOtherAddressStateOrProvince",				"State or province of other address" },
	{ 0x3a63, 0x001e, "PidTagOtherAddressStreet",					"Street of other address" },
	{ 0x3a64, 0x001e, "PidTagOtherAddressPostOfficeBox",				"Post office box of other address" },

	{ 0x3a70, 0x1102, "PidTagUserX509Certificate",					"User X.509 certificate" },
	{ 0x3a71, 0x0003, "PidTagSendInternetEncoding",					"Message encoding preference flags" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The distribution list property type (0x3c00 - 0x3cff)
 */
libfmapi_property_type_t libfmapi_distribution_list_property_types[ ] = {

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The profile property type (0x3d00 - 0x3dff)
 */
libfmapi_property_type_t libfmapi_profile_property_types[ ] = {
	{ 0x3d00, 0x0102, "PR_STORE_PROVIDERS",						"" },
	{ 0x3d01, 0x0102, "PR_AB_PROVIDERS",						"" },
	{ 0x3d02, 0x0102, "PR_TRANSPORT_PROVIDERS",					"" },
	{ 0x3d04, 0x000b, "PR_DEFAULT_PROFILE",						"" },
	{ 0x3d05, 0x1102, "PR_AB_SEARCH_PATH",						"" },
	{ 0x3d06, 0x0102, "PR_AB_DEFAULT_DIR",						"" },
	{ 0x3d07, 0x0102, "PR_AB_DEFAULT_PAB",						"" },
	{ 0x3d08, 0x0102, "PR_FILTERING_HOOKS",						"" },
	{ 0x3d09, 0x001e, "PR_SERVICE_NAME",						"" },
	{ 0x3d0a, 0x001e, "PR_SERVICE_DLL_NAME",					"" },
	{ 0x3d0b, 0x001e, "PR_SERVICE_ENTRY_NAME",					"" },
	{ 0x3d0c, 0x0102, "PR_SERVICE_UID",						"" },
	{ 0x3d0d, 0x0102, "PR_SERVICE_EXTRA_UIDS",					"" },
	{ 0x3d0e, 0x0102, "PR_SERVICES",						"" },
	{ 0x3d0f, 0x101e, "PR_SERVICE_SUPPORT_FILES",					"" },
	{ 0x3d10, 0x101e, "PR_SERVICE_DELETE_FILES",					"" },
	{ 0x3d11, 0x0102, "PR_AB_SEARCH_PATH_UPDATE",					"" },
	{ 0x3d12, 0x001e, "PR_PROFILE_NAME",						"" },
	{ 0x3d13, 0x001e, "PR_SERVICE_INSTALL_ID",					"" },
	{ 0x3d21, 0x0102, "ptagAdminNTSD",						"Administrator permissions (NT security descriptor)" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The status object property type (0x3e00 - 0x3fff)
 */
libfmapi_property_type_t libfmapi_status_object_property_types[ ] = {
	{ 0x3e00, 0x001e, "PR_IDENTITY_DISPLAY",					"" },
	{ 0x3e01, 0x0102, "PR_IDENTITY_ENTRYID",					"" },
	{ 0x3e02, 0x0003, "PR_RESOURCE_METHODS",					"" },
	{ 0x3e03, 0x0003, "PR_RESOURCE_TYPE",						"" },
	{ 0x3e04, 0x0003, "PR_STATUS_CODE",						"" },
	{ 0x3e05, 0x0102, "PR_IDENTITY_SEARCH_KEY",					"" },
	{ 0x3e06, 0x0102, "PR_OWN_STORE_ENTRYID",					"" },
	{ 0x3e07, 0x001e, "PR_RESOURCE_PATH",						"" },
	{ 0x3e08, 0x001e, "PR_STATUS_STRING",						"" },
	{ 0x3e09, 0x000b, "PR_X400_DEFERRED_DELIVERY_CANCEL",				"" },
	{ 0x3e0a, 0x0102, "PR_HEADER_FOLDER_ENTRYID",					"" },
	{ 0x3e0b, 0x0003, "PR_REMOTE_PROGRESS",						"" },
	{ 0x3e0c, 0x001e, "PR_REMOTE_PROGRESS_TEXT",					"" },
	{ 0x3e0d, 0x000b, "PR_REMOTE_VALIDATE_OK",					"" },

	{ 0x3f00, 0x0003, "PR_CONTROL_FLAGS",						"Dialog box control behavior flags" },
	{ 0x3f01, 0x0102, "PR_CONTROL_STRUCTURE",					"Dialog box control structure" },
	{ 0x3f02, 0x0003, "PR_CONTROL_TYPE",						"Dialog box control type" },
	{ 0x3f03, 0x0003, "PR_DELTAX",							"Dialog box control width" },
	{ 0x3f04, 0x0003, "PR_DELTAY",							"Dialog box control height" },
	{ 0x3f05, 0x0003, "PR_XPOS",							"Dialog box control left x coordinate" },
	{ 0x3f06, 0x0003, "PR_YPOS",							"Dialog box control upper y coordinate" },
	{ 0x3f07, 0x0102, "PR_CONTROL_ID",						"Dialog box control identifier" },
	{ 0x3f08, 0x0003, "PR_INITIAL_DETAILS_PANE",					"Initial property page" },

	{ 0x3f80, 0x0014, "PR_DID",							"" },
	{ 0x3f81, 0x0014, "PR_SEQID",							"" },
	{ 0x3f82, 0x0014, "PR_DRAFTID",							"" },
	{ 0x3f83, 0x0040, "PR_CHECK_IN_TIME",						"" },
	{ 0x3f84, 0x001e, "PR_CHECK_IN_COMMENT",					"" },
	{ 0x3f85, 0x0003, "PR_VERSION_OP_CODE",						"" },
	{ 0x3f86, 0x0102, "PR_VERSION_OP_DATA",						"" },
	{ 0x3f87, 0x0003, "PR_VERSION_SEQUENCE_NUMBER",					"" },
	{ 0x3f88, 0x0014, "PR_ATTACH_ID",						"" },
	{ 0x3f8d, 0x001e, "PR_PKM_DOC_STATUS",						"" },
	{ 0x3f8e, 0x101e, "PR_MV_PKM_OPERATION_REQ",					"" },
	{ 0x3f8f, 0x001e, "PR_PKM_DOC_INTERNAL_STATE",					"" },
	{ 0x3f90, 0x0002, "PR_VERSIONING_FLAGS",					"" },
	{ 0x3f91, 0x0102, "PR_PKM_LAST_UNAPPROVED_VID",					"" },
	{ 0x3f92, 0x101e, "PR_MV_PKM_VERSION_LABELS",					"" },
	{ 0x3f93, 0x101e, "PR_MV_PKM_VERSION_STATUS",					"" },
	{ 0x3f94, 0x0102, "PR_PKM_INTERNAL_DATA",					"" },
	{ 0x3fc9, 0x0102, "PR_LAST_CONFLICT",						"" },
	{ 0x3fca, 0x0102, "PR_CONFLICT_MSG_KEY",					"" },
	{ 0x3fd0, 0x0102, "PR_REPL_HEADER",						"" },
	{ 0x3fd1, 0x0102, "PR_REPL_STATUS",						"" },
	{ 0x3fd2, 0x0102, "PR_REPL_CHANGES",						"" },
	{ 0x3fd3, 0x0102, "PR_REPL_RGM",						"" },
	{ 0x3fd4, 0x0102, "PR_RMI",							"" },
	{ 0x3fd5, 0x0102, "PR_INTERNAL_POST_REPLY",					"" },
	{ 0x3fd6, 0x0040, "PR_NTSD_MODIFICATION_TIME",					"" },
	{ 0x3fd8, 0x001e, "PR_PREVIEW_UNREAD",						"" },
	{ 0x3fd9, 0x001e, "PR_PREVIEW",							"" },
	{ 0x3fda, 0x001e, "PR_ABSTRACT",						"" },
	{ 0x3fdb, 0x0003, "PR_DL_REPORT_FLAGS",						"" },
	{ 0x3fdc, 0x0102, "PR_BILATERAL_INFO",						"" },
	{ 0x3fdd, 0x0003, "PR_MSG_BODY_ID",						"" },
	{ 0x3fde, 0x0003, "PidTagInternetCodepage",					"Message body codepage" },
	{ 0x3fdf, 0x0003, "PidTagAutoResponseSuppress",					"Suppress auto response" },
	{ 0x3fe0, 0x000d, "PR_ACL_TABLE",						"Access control list table object" },
	{ 0x3fe0, 0x0102, "PR_ACL_DATA",						"Access control list data" },
	{ 0x3fe1, 0x000d, "PidTagRulesTable",						"Folder rules table object" },
	{ 0x3fe1, 0x0102, "PidTagRulesData",						"Folder rules table data" },
	{ 0x3fe2, 0x0003, "PR_FOLDER_DESIGN_FLAGS",					"" },
	{ 0x3fe3, 0x000b, "PR_DELEGATED_BY_RULE",					"" },
	{ 0x3fe4, 0x000b, "PR_DESIGN_IN_PROGRESS",					"" },
	{ 0x3fe5, 0x000b, "PR_SECURE_ORIGINATION",					"" },
	{ 0x3fe6, 0x000b, "PR_PUBLISH_IN_ADDRESS_BOOK",					"" },
	{ 0x3fe7, 0x0003, "PidTagResolveMethod",					"Conflict resolution method" },
	{ 0x3fe8, 0x001e, "PR_ADDRESS_BOOK_DISPLAY_NAME",				"" },
	{ 0x3fe9, 0x0003, "PR_EFORMS_LOCALE_ID",					"" },
	{ 0x3fea, 0x000b, "PR_HAS_DAMS",						"" },
	{ 0x3feb, 0x0003, "PR_DEFERRED_SEND_NUMBER",					"" },
	{ 0x3fec, 0x0003, "PR_DEFERRED_SEND_UNITS",					"" },
	{ 0x3fed, 0x0003, "PR_EXPIRY_NUMBER",						"" },
	{ 0x3fee, 0x0003, "PR_EXPIRY_UNITS",						"" },
	{ 0x3fef, 0x0040, "PR_DEFERRED_SEND_TIME",					"" },
	{ 0x3ff0, 0x0102, "PidTagConflictEntryId",					"Conflict entry identifier" },
	{ 0x3ff1, 0x0003, "PidTagMessageLocaleId",					"Message locale identifier" },
	{ 0x3ff2, 0x0102, "PR_RULE_TRIGGER_HISTORY",					"" },
	{ 0x3ff3, 0x0102, "PR_MOVE_TO_STORE_ENTRYID",					"" },
	{ 0x3ff4, 0x0102, "PR_MOVE_TO_FOLDER_ENTRYID",					"" },
	{ 0x3ff5, 0x0003, "PR_STORAGE_QUOTA_LIMIT",					"" },
	{ 0x3ff6, 0x0003, "PR_EXCESS_STORAGE_USED",					"" },
	{ 0x3ff7, 0x001e, "PR_SVR_GENERATING_QUOTA_MSG",				"" },
	{ 0x3ff8, 0x001e, "PR_CREATOR_NAME",						"Creator name" },
	{ 0x3ff9, 0x0102, "PR_CREATOR_ENTRYID",						"Creator entry identifier" },
	{ 0x3ffa, 0x001e, "PR_LAST_MODIFIER_NAME",					"Last modifier name" },
	{ 0x3ffb, 0x0102, "PR_LAST_MODIFIER_ENTRYID",					"Last modifier entry identifier" },
	{ 0x3ffc, 0x001e, "PR_REPLY_RECIPIENT_SMTP_PROXIES",				"" },
	{ 0x3ffd, 0x0003, "PidTagMessageCodepage",					"Message codepage" },
	{ 0x3ffe, 0x0102, "PR_EXTENDED_ACL_DATA",					"" },
	{ 0x3fff, 0x000b, "PR_FROM_I_HAVE",						"" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The transport provider message envelope property type (0x4000 - 0x57ff)
 */
libfmapi_property_type_t libfmapi_transport_provider_message_envelope_property_types[ ] = {
	{ 0x4000, 0x0003, "PR_NEW_ATTACH",						"" },
	{ 0x4001, 0x0003, "PR_START_EMBED",						"" },
	{ 0x4002, 0x0003, "PR_END_EMBED",						"" },
	{ 0x4003, 0x0003, "PR_START_RECIP",						"" },
	{ 0x4004, 0x0003, "PR_END_RECIP",						"" },
	{ 0x4005, 0x0003, "PR_END_CC_RECIP",						"" },
	{ 0x4006, 0x0003, "PR_END_BCC_RECIP",						"" },
	{ 0x4007, 0x0003, "PR_END_P1_RECIP",						"" },
	{ 0x4009, 0x0003, "PR_START_TOP_FLD",						"" },
	{ 0x400a, 0x0003, "PR_START_SUB_FLD",						"" },
	{ 0x400b, 0x0003, "PR_END_FOLDER",						"" },
	{ 0x400c, 0x0003, "PR_START_MESSAGE",						"" },
	{ 0x400d, 0x0003, "PR_END_MESSAGE",						"" },
	{ 0x400e, 0x0003, "PR_END_ATTACH",						"" },
	{ 0x400f, 0x0003, "PR_EC_WARNING",						"" },
	{ 0x4010, 0x0003, "PR_START_FAI_MSG",						"" },
	{ 0x4011, 0x0102, "PR_NEW_FX_FOLDER",						"" },
	{ 0x4012, 0x0003, "PR_INCR_SYNC_CHG",						"" },
	{ 0x4013, 0x0003, "PR_INCR_SYNC_DEL",						"" },
	{ 0x4014, 0x0003, "PR_INCR_SYNC_END",						"" },
	{ 0x4015, 0x0003, "PR_INCR_SYNC_MSG",						"" },
	{ 0x4016, 0x0003, "PR_FX_DEL_PROP",						"" },
	{ 0x4017, 0x0003, "PR_IDSET_GIVEN",						"" },
	{ 0x4019, 0x0003, "PR_SENDER_FLAGS",						"Sender flags" },
	{ 0x401a, 0x0003, "PR_SENT_REPRESENTING_FLAGS",					"Sent representing flags" },
	{ 0x401b, 0x0003, "PR_RCVD_BY_FLAGS",						"Received by flags" },
	{ 0x401c, 0x0003, "PR_RCVD_REPRESENTING_FLAGS",					"Received representing flags" },
	{ 0x401d, 0x0003, "PR_ORIGINAL_SENDER_FLAGS",					"Original sender flags" },
	{ 0x401e, 0x0003, "PR_ORIGINAL_SENT_REPRESENTING_FLAGS",			"Original sent representing flags" },
	{ 0x401f, 0x0003, "PR_REPORT_FLAGS",						"" },
	{ 0x4020, 0x0003, "PR_READ_RECEIPT_FLAGS",					"" },
	{ 0x4021, 0x000b, "PR_SOFT_DELETES",						"" },
	{ 0x402c, 0x0102, "PR_MESSAGE_SUBMISSION_ID_FROM_CLIENT",			"" },
	{ 0x4030, 0x001e, "PR_SENDER_SIMPLE_DISP_NAME",					"" },
	{ 0x4031, 0x001e, "PR_SENT_REPRESENTING_SIMPLE_DISP_NAME",			"" },
	{ 0x4038, 0x001e, "PR_CREATOR_SIMPLE_DISP_NAME",				"" },
	{ 0x403d, 0x001e, "PR_ORG_ADDR_TYPE",						"Original address type" },
	{ 0x403e, 0x001e, "PR_ORG_EMAIL_ADDR",						"Original e-mail address" },
	{ 0x4059, 0x0003, "PR_CREATOR_FLAGS",						"" },
	{ 0x405a, 0x0003, "PR_MODIFIER_FLAGS",						"" },
	{ 0x405b, 0x0003, "PR_ORIGINATOR_FLAGS",					"" },
	{ 0x405c, 0x0003, "PR_REPORT_DESTINATION_FLAGS",				"" },
	{ 0x405d, 0x0003, "PR_ORIGINAL_AUTHOR_FLAGS",					"Original author flags" },
	{ 0x4061, 0x0102, "PR_ORIGINATOR_SEARCH_KEY",					"" },
	{ 0x4064, 0x0102, "PR_REPORT_DESTINATION_SEARCH_KEY",				"" },
	{ 0x4065, 0x0003, "PR_ER_FLAG",							"" },
	{ 0x4068, 0x0102, "PR_INTERNET_SUBJECT",					"" },
	{ 0x4069, 0x0102, "PR_INTERNET_SENT_REPRESENTING_NAME",				"" },
	{ 0x4076, 0x0003, "PR_CONTENT_FILTER_SCL",					"" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The transport provider recipient property type (0x5800 - 0x5fff)
 */
libfmapi_property_type_t libfmapi_transport_provider_recipient_property_types[ ] = {
	{ 0x5902, 0x0003, "PR_INET_MAIL_OVERRIDE_FORMAT",				"" },
	{ 0x5909, 0x0003, "PidTagMessageEditorFormat",					"Message editor format" },
	{ 0x5ff6, 0x001e, "PR_RECIPIENT_DISPLAY_NAME",					"" },
	{ 0x5ff7, 0x0102, "PR_RECIPIENT_ENTRYID",					"" },
	{ 0x5ffb, 0x0040, "PR_RECIPIENT_TRACKSTATUS_ME",				"" },
	{ 0x5ffd, 0x0003, "PR_RECIPIENTS_FLAGS",					"" },
	{ 0x5fff, 0x0003, "PR_RECIPIENT_TRACKSTATUS",					"" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The client non-transmittable message property type (0x6000 - 0x65ff)
 */
libfmapi_property_type_t libfmapi_client_non_transmittable_message_property_types[ ] = {
	{ 0x6001, 0x0003, "PR_DOTSTUFF_STATE",						"" },
	{ 0x6001, 0x001e, "",								"Alias" },
	{ 0x65a0, 0x0014, "PR_RULE_SERVER_RULE_ID",					"" },
	{ 0x65c2, 0x0102, "PR_REPLY_TEMPLATE_ID",					"" },
	{ 0x65c6, 0x0003, "PidTagSecureSubmitFlags",					"Secure submit flags" },
	{ 0x65e0, 0x0102, "PidTagSourceKey",						"Source key" },
	{ 0x65e1, 0x0102, "PidTagParentSourceKey",					"Parent source key" },
	{ 0x65e2, 0x0102, "PidTagChangeKey",						"Change key" },
	{ 0x65e3, 0x0102, "PidTagPredecessorChangeList",				"Predecessor change list" },
	{ 0x65e4, 0x0003, "PR_SYNCHRONIZE_FLAGS",					"" },
	{ 0x65e5, 0x000b, "PR_AUTO_ADD_NEW_SUBS",					"" },
	{ 0x65e6, 0x000b, "PR_NEW_SUBS_GET_AUTO_ADD",					"" },
	{ 0x65e7, 0x001e, "PR_MESSAGE_SITE_NAME",					"" },
	{ 0x65e8, 0x000b, "PR_MESSAGE_PROCESSED",					"" },
	{ 0x65e9, 0x0003, "PR_RULE_MSG_STATE",						"" },
	{ 0x65ea, 0x0003, "PR_RULE_MSG_USER_FLAGS",					"" },
	{ 0x65eb, 0x001e, "PR_RULE_MSG_PROVIDER",					"" },
	{ 0x65ec, 0x001e, "PR_RULE_MSG_NAME",						"" },
	{ 0x65ed, 0x0003, "PR_RULE_MSG_LEVEL",						"" },
	{ 0x65ee, 0x0102, "PR_RULE_MSG_PROVIDER_DATA",					"" },
	{ 0x65ef, 0x0102, "PR_RULE_MSG_ACTIONS",					"" },
	{ 0x65f0, 0x0102, "PR_RULE_MSG_CONDITION",					"" },
	{ 0x65f1, 0x0003, "PR_RULE_MSG_CONDITION_LCID",					"" },
	{ 0x65f2, 0x0002, "PR_RULE_MSG_VERSION",					"" },
	{ 0x65f3, 0x0003, "PR_RULE_MSG_SEQUENCE",					"" },
	{ 0x65f4, 0x000b, "PR_PREVENT_MSG_CREATE",					"" },
	{ 0x65f5, 0x0040, "PR_IMAP_INTERNAL_DATE",					"" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The service provider non-transmittable property type (0x6600 - 0x67ef)
 */
libfmapi_property_type_t libfmapi_service_provider_non_transmittable_property_types[ ] = {
	{ 0x6600, 0x0003, "PR_PROFILE_VERSION",						"" },
	{ 0x6601, 0x0003, "PR_PROFILE_CONFIG_FLAGS",					"" },
	{ 0x6602, 0x001e, "PR_PROFILE_HOME_SERVER",					"" },
	{ 0x6603, 0x001e, "PR_PROFILE_USER",						"" },
	{ 0x6604, 0x0003, "PR_PROFILE_CONNECT_FLAGS",					"Profile connection flags" },
	{ 0x6605, 0x0003, "PR_PROFILE_TRANSPORT_FLAGS",					"" },
	{ 0x6606, 0x0003, "PR_PROFILE_UI_STATE",					"" },
	{ 0x6607, 0x001e, "PR_PROFILE_UNRESOLVED_NAME",					"" },
	{ 0x6608, 0x001e, "PR_PROFILE_UNRESOLVED_SERVER",				"" },
	{ 0x6609, 0x0003, "PR_PROFILE_OPEN_FLAGS",					"" },
	{ 0x6609, 0x001e, "PR_PROFILE_BINDING_ORDER",					"" },
	{ 0x660a, 0x0003, "PR_PROFILE_TYPE",						"" },
	{ 0x660b, 0x001e, "PR_PROFILE_MAILBOX",						"" },
	{ 0x660c, 0x001e, "PR_PROFILE_SERVER",						"" },
	{ 0x660d, 0x0003, "PR_PROFILE_MAX_RESTRICT",					"" },
	{ 0x660e, 0x001e, "PR_PROFILE_AB_FILES_PATH",					"" },
	{ 0x660f, 0x001e, "PR_PROFILE_FAVFLD_DISPLAY_NAME",				"" },
	{ 0x6610, 0x0003, "PR_INTERNET_MESSAGE_FORMAT",					"" },
	{ 0x6610, 0x001e, "PR_PROFILE_OFFLINE_STORE_PATH",				"" },
	{ 0x6611, 0x0003, "PidTagContactAddressBookStoreSupportMask",			"Contact address book store support flags" },
	{ 0x6611, 0x0102, "PR_PROFILE_OFFLINE_INFO",					"" },
	{ 0x6612, 0x0003, "PR_INTERNET_WRAPPING_LENGTH",				"" },
	{ 0x6612, 0x001e, "PR_PROFILE_HOME_SERVER_DN",					"" },
	{ 0x6613, 0x101e, "PR_PROFILE_HOME_SERVER_ADDRS",				"" },
	{ 0x6614, 0x001e, "PR_PROFILE_SERVER_DN",					"" },
	{ 0x6615, 0x001e, "PR_PROFILE_FAVFLD_COMMENT",					"" },
	{ 0x6616, 0x001e, "PR_PROFILE_ALLPUB_DISPLAY_NAME",				"" },
	{ 0x6617, 0x001e, "PR_PROFILE_ALLPUB_COMMENT",					"" },
	{ 0x6618, 0x0003, "PR_DISABLE_WINSOCK",						"" },
	{ 0x6618, 0x000b, "PR_IN_TRANSIT",						"" },
	{ 0x6619, 0x0003, "PR_PROFILE_AUTH_PACKAGE",					"" },
	{ 0x6619, 0x001e, "PidTagPstBodyPrefix",					"Body prefix" },
	{ 0x6619, 0x0102, "PR_USER_ENTRYID",						"" },
	{ 0x661a, 0x001e, "PR_USER_NAME",						"" },
	{ 0x661b, 0x0102, "PR_MAILBOX_OWNER_ENTRYID",					"" },
	{ 0x661c, 0x001e, "PR_MAILBOX_OWNER_NAME",					"" },
	{ 0x661d, 0x0003, "PidTagPstBestBodyProptag",					"" },
	{ 0x661d, 0x000b, "PR_OOF_STATE",						"" },
	{ 0x661e, 0x0102, "PR_SCHEDULE_FOLDER_ENTRYID",					"" },
	{ 0x661f, 0x0102, "PR_IPM_DAF_ENTRYID",						"" },
	{ 0x6620, 0x0102, "PidTagNonIpmSubtreeEntryId",					"Non-IPM subtree entry identifier" },
	{ 0x6620, 0x1102, "PidTagContactAddressBookFolderEntryIds",			"Contact address book entry identifiers" },
	{ 0x6621, 0x0102, "PR_EFORMS_REGISTRY_ENTRYID",					"" },
	{ 0x6621, 0x1102, "PidTagContactAddressBookStoreSupportMasks",			"Contact address book store support flags" },
	{ 0x6622, 0x0102, "PR_SPLUS_FREE_BUSY_ENTRYID",					"" },
	{ 0x6623, 0x0003, "PR_ROH_FLAGS",						"RPC over HTTP flags" },
	{ 0x6623, 0x001e, "PR_HIERARCHY_SERVER",					"" },
	{ 0x6623, 0x0102, "PR_OFFLINE_ADDRBOOK_ENTRYID",				"" },
	{ 0x6624, 0x0102, "PR_EFORMS_FOR_LOCALE_ENTRYID",				"" },
	{ 0x6625, 0x0102, "PR_FREE_BUSY_FOR_LOCAL_SITE_ENTRYID",			"" },
	{ 0x6626, 0x0102, "PR_ADDRBOOK_FOR_LOCAL_SITE_ENTRYID",				"" },
	{ 0x6627, 0x0003, "PR_ROH_PROXY_AUTH_SCHEME",					"RPC over HTTP proxy authentication scheme" },
	{ 0x6627, 0x0102, "PR_OFFLINE_MESSAGE_ENTRYID",					"" },
	{ 0x6628, 0x0102, "PR_GW_MTSIN_ENTRYID",					"" },
	{ 0x6629, 0x0102, "PR_GW_MTSOUT_ENTRYID",					"" },
	{ 0x662a, 0x000b, "PR_TRANSFER_ENABLED",					"" },
	{ 0x662b, 0x0102, "PR_TEST_LINE_SPEED",						"" },
	{ 0x662c, 0x000d, "PR_HIERARCHY_SYNCHRONIZER",					"" },
	{ 0x662d, 0x000d, "PR_CONTENTS_SYNCHRONIZER",					"" },
	{ 0x662e, 0x000d, "PR_COLLECTOR",						"" },
	{ 0x662f, 0x000d, "PR_FAST_TRANSFER",						"" },
	{ 0x6630, 0x0102, "PR_IPM_FAVORITES_ENTRYID",					"" },
	{ 0x6631, 0x0102, "PR_IPM_PUBLIC_FOLDERS_ENTRYID",				"" },
	{ 0x6632, 0x000b, "PR_STORE_OFFLINE",						"" },
	{ 0x6633, 0x000b, "PidTagPstLrnorestrictions",					"" },
	{ 0x6634, 0x000d, "PR_CHANGE_ADVISOR",						"" },
	{ 0x6635, 0x0003, "PidTagPstHiddenCount",					"Number of hidden items" },
	{ 0x6635, 0x001e, "PR_FAVORITES_DEFAULT_NAME",					"" },
	{ 0x6636, 0x0003, "PidTagPstHiddenUnread",					"Number of unread hidden items" },
	{ 0x6636, 0x0102, "PR_SYS_CONFIG_FOLDER_ENTRYID",				"" },
	{ 0x6637, 0x0048, "PR_CHANGE_NOTIFICATION_GUID",				"" },
	{ 0x6638, 0x0003, "PR_FOLDER_CHILD_COUNT",					"Number of sub folders" },
	{ 0x6639, 0x0003, "PR_RIGHTS",							"" },
	{ 0x663a, 0x000b, "PidTagHasRules",						"Has email rules" },
	{ 0x663b, 0x0102, "PidTagAddressBookEntryId",					"Address book entry identifier" },
	{ 0x663c, 0x0102, "PR_PUBLIC_FOLDER_ENTRYID",					"" },
	{ 0x663d, 0x0003, "PR_OFFLINE_FLAGS",						"" },
	{ 0x663e, 0x0003, "PidTagHierarchyChangeNumber",				"Hierarchy change number" },
	{ 0x663f, 0x000b, "PR_HAS_MODERATOR_RULES",					"" },
	{ 0x6640, 0x0003, "PR_DELETED_MSG_COUNT",					"" },
	{ 0x6641, 0x0003, "PR_DELETED_FOLDER_COUNT",					"" },
	{ 0x6642, 0x0040, "PR_OLDEST_DELETED_ON",					"" },
	{ 0x6643, 0x0003, "PR_DELETED_ASSOC_MSG_COUNT",					"" },
	{ 0x6644, 0x001e, "PR_REPLICA_SERVER",						"" },
	{ 0x6645, 0x0102, "PR_CLIENT_ACTIONS",						"" },
	{ 0x6646, 0x0102, "PR_DAM_ORIGINAL_ENTRYID",					"" },
	{ 0x6647, 0x000b, "PR_DAM_BACK_PATCHED",					"" },
	{ 0x6648, 0x0003, "PR_RULE_ERROR",						"" },
	{ 0x6649, 0x0003, "PR_RULE_ACTION_TYPE",					"" },
	{ 0x664a, 0x000b, "PR_HAS_NAMED_PROPERTIES",					"" },
	{ 0x664b, 0x0014, "PR_REPLICA_VERSION",						"" },
	{ 0x6650, 0x0003, "PR_RULE_ACTION_NUMBER",					"" },
	{ 0x6651, 0x0102, "PR_RULE_FOLDER_ENTRYID",					"" },
	{ 0x6652, 0x0102, "PR_ACTIVE_USER_ENTRYID",					"" },
	{ 0x6653, 0x0003, "PR_0X400_ENVELOPE_TYPE",					"" },
	{ 0x6654, 0x0040, "PR_MSG_FOLD_TIME",						"" },
	{ 0x6655, 0x0102, "PR_ICS_CHANGE_KEY",						"" },
	{ 0x6658, 0x0003, "PR_GW_ADMIN_OPERATIONS",					"" },
	{ 0x6659, 0x0102, "PR_INTERNET_CONTENT",					"" },
	{ 0x665a, 0x000b, "PR_HAS_ATTACH_FROM_IMAIL",					"" },
	{ 0x665b, 0x001e, "PR_ORIGINATOR_NAME",						"" },
	{ 0x665c, 0x001e, "PR_ORIGINATOR_ADDR",						"" },
	{ 0x665d, 0x001e, "PR_ORIGINATOR_ADDRTYPE",					"" },
	{ 0x665e, 0x0102, "PR_ORIGINATOR_ENTRYID",					"" },
	{ 0x665f, 0x0040, "PR_ARRIVAL_TIME",						"" },
	{ 0x6660, 0x0102, "PR_TRACE_INFO",						"" },
	{ 0x6661, 0x0102, "PR_SUBJECT_TRACE_INFO",					"" },
	{ 0x6662, 0x0003, "PR_RECIPIENT_NUMBER",					"" },
	{ 0x6663, 0x0102, "PR_MTS_SUBJECT_ID",						"" },
	{ 0x6664, 0x001e, "PR_REPORT_DESTINATION_NAME",					"" },
	{ 0x6665, 0x0102, "PR_REPORT_DESTINATION_ENTRYID",				"" },
	{ 0x6666, 0x0102, "PR_CONTENT_SEARCH_KEY",					"" },
	{ 0x6667, 0x0102, "PR_FOREIGN_ID",						"" },
	{ 0x6668, 0x0102, "PR_FOREIGN_REPORT_ID",					"" },
	{ 0x6669, 0x0102, "PR_FOREIGN_SUBJECT_ID",					"" },
	{ 0x666a, 0x0102, "PR_INTERNAL_TRACE_INFO",					"" },
	{ 0x666c, 0x000b, "PR_IN_CONFLICT",						"" },
	{ 0x6670, 0x0102, "PR_LONGTERM_ENTRYID_FROM_TABLE",				"" },
	{ 0x6671, 0x0014, "PR_MEMBER_ID",						"" },
	{ 0x6672, 0x001e, "PR_MEMBER_NAME",						"" },
	{ 0x6673, 0x0003, "PR_MEMBER_RIGHTS",						"" },
	{ 0x6674, 0x0014, "PR_RULE_ID",							"" },
	{ 0x6675, 0x0102, "PR_RULE_IDS",						"" },
	{ 0x6676, 0x0003, "PR_RULE_SEQUENCE",						"" },
	{ 0x6677, 0x0003, "PR_RULE_STATE",						"" },
	{ 0x6678, 0x0003, "PR_RULE_USER_FLAGS",						"" },
	{ 0x6679, 0x00fd, "PR_RULE_CONDITION",						"" },
	{ 0x667b, 0x001e, "PR_PROFILE_MOAB",						"" },
	{ 0x667c, 0x001e, "PR_PROFILE_MOAB_GUID",					"" },
	{ 0x667d, 0x0003, "PR_PROFILE_MOAB_SEQ",					"" },
	{ 0x667f, 0x1102, "PR_IMPLIED_RESTRICTIONS",					"" },
	{ 0x6680, 0x00fe, "PR_RULE_ACTIONS",						"" },
	{ 0x6681, 0x001e, "PR_RULE_PROVIDER",						"" },
	{ 0x6682, 0x001e, "PR_RULE_NAME",						"" },
	{ 0x6683, 0x0003, "PR_RULE_LEVEL",						"" },
	{ 0x6684, 0x0102, "PR_RULE_PROVIDER_DATA",					"" },
	{ 0x6685, 0x0040, "PR_LAST_FULL_BACKUP",					"" },
	{ 0x6687, 0x0102, "PR_PROFILE_ADDR_INFO",					"" },
	{ 0x6689, 0x0102, "PR_PROFILE_OPTIONS_DATA",					"" },
	{ 0x668a, 0x0102, "PR_EVENTS_ROOT_FOLDER_ENTRYID",				"" },
	{ 0x668d, 0x001e, "PR_INBOUND_NEWSFEED_DN",					"" },
	{ 0x668e, 0x001e, "PR_OUTBOUND_NEWSFEED_DN",					"" },
	{ 0x668f, 0x0040, "PidTagDeletedOn",						"Soft-deletion time" },
	{ 0x6690, 0x0003, "PR_REPLICATION_STYLE",					"" },
	{ 0x6691, 0x0102, "PR_REPLICATION_SCHEDULE",					"" },
	{ 0x6692, 0x0003, "PR_REPLICATION_MESSAGE_PRIORITY",				"" },
	{ 0x6693, 0x0003, "PR_OVERALL_MSG_AGE_LIMIT",					"" },
	{ 0x6694, 0x0003, "PR_REPLICATION_ALWAYS_INTERVAL",				"" },
	{ 0x6695, 0x0003, "PR_REPLICATION_MSG_SIZE",					"" },
	{ 0x6696, 0x000b, "PR_IS_NEWSGROUP_ANCHOR",					"" },
	{ 0x6697, 0x000b, "PR_IS_NEWSGROUP",						"" },
	{ 0x6698, 0x0102, "PR_REPLICA_LIST",						"" },
	{ 0x6699, 0x0003, "PR_OVERALL_AGE_LIMIT",					"" },
	{ 0x669a, 0x001e, "PR_INTERNET_CHARSET",					"" },
	{ 0x669b, 0x0014, "PR_DELETED_MESSAGE_SIZE_EXTENDED",				"" },
	{ 0x669c, 0x0014, "PR_DELETED_NORMAL_MESSAGE_SIZE_EXTENDED",			"" },
	{ 0x669d, 0x0014, "PR_DELETED_ASSOC_MESSAGE_SIZE_EXTENDED",			"" },
	{ 0x669e, 0x000b, "PR_SECURE_IN_SITE",						"" },
	{ 0x66a0, 0x001e, "PR_NT_USER_NAME",						"" },
	{ 0x66a1, 0x0003, "PR_LOCALE_ID",						"" },
	{ 0x66a2, 0x0040, "PR_LAST_LOGON_TIME",						"" },
	{ 0x66a3, 0x0040, "PR_LAST_LOGOFF_TIME",					"" },
	{ 0x66a4, 0x0003, "PR_STORAGE_LIMIT_INFORMATION",				"" },
	{ 0x66a5, 0x001e, "PR_NEWSGROUP_COMPONENT",					"" },
	{ 0x66a6, 0x0102, "PR_NEWSFEED_INFO",						"" },
	{ 0x66a7, 0x001e, "PR_INTERNET_NEWSGROUP_NAME",					"" },
	{ 0x66a8, 0x0003, "PR_FOLDER_FLAGS",						"" },
	{ 0x66a9, 0x0040, "PR_LAST_ACCESS_TIME",					"" },
	{ 0x66aa, 0x0003, "PR_RESTRICTION_COUNT",					"" },
	{ 0x66ab, 0x0003, "PR_CATEG_COUNT",						"" },
	{ 0x66ac, 0x0003, "PR_CACHED_COLUMN_COUNT",					"" },
	{ 0x66ad, 0x0003, "PR_NORMAL_MSG_W_ATTACH_COUNT",				"" },
	{ 0x66ae, 0x0003, "PR_ASSOC_MSG_W_ATTACH_COUNT",				"" },
	{ 0x66af, 0x0003, "PR_RECIPIENT_ON_NORMAL_MSG_COUNT",				"" },
	{ 0x66b0, 0x0003, "PR_RECIPIENT_ON_ASSOC_MSG_COUNT",				"" },
	{ 0x66b1, 0x0003, "PR_ATTACH_ON_NORMAL_MSG_COUNT",				"" },
	{ 0x66b2, 0x0003, "PR_ATTACH_ON_ASSOC_MSG_COUNT",				"" },
	{ 0x66b3, 0x0003, "PR_NORMAL_MESSAGE_SIZE",					"" },
	{ 0x66b3, 0x0014, "PR_NORMAL_MESSAGE_SIZE_EXTENDED",				"" },
	{ 0x66b4, 0x0003, "PR_ASSOC_MESSAGE_SIZE",					"" },
	{ 0x66b4, 0x0014, "PR_ASSOC_MESSAGE_SIZE_EXTENDED",				"" },
	{ 0x66b5, 0x001e, "PR_FOLDER_PATHNAME",						"" },
	{ 0x66b6, 0x0003, "PR_OWNER_COUNT",						"" },
	{ 0x66b7, 0x0003, "PR_CONTACT_COUNT",						"" },
	{ 0x66c3, 0x0003, "PR_CODE_PAGE_ID",						"" },
	{ 0x66c4, 0x0003, "PR_RETENTION_AGE_LIMIT",					"" },
	{ 0x66c5, 0x000b, "PR_DISABLE_PERUSER_READ",					"Disable per-user read/unread processing" },
	{ 0x66c6, 0x0102, "PR_INTERNET_PARSE_STATE",					"" },
	{ 0x66c7, 0x0102, "PR_INTERNET_MESSAGE_INFO",					"" },
	{ 0x66fa, 0x0003, "PidTagLatestPstEnsure",					"" },

	{ 0x6700, 0x001e, "PR_PST_PATH",						"" },
	{ 0x6701, 0x000b, "PR_PST_REMEMBER_PW",						"" },
	{ 0x6702, 0x0003, "PR_OST_ENCRYPTION",						"" },
	{ 0x6703, 0x001e, "PR_PST_PW_SZ_OLD",						"" },
	{ 0x6704, 0x001e, "PR_PST_PW_SZ_NEW",						"" },
	{ 0x6705, 0x0003, "PR_SORT_LOCALE_ID",						"" },
	{ 0x6705, 0x000b, "PidTagPstImpsubtreeDescendant",				"" },
	{ 0x6707, 0x001e, "PidTagUrlName",						"Object URL" },
	{ 0x6709, 0x0040, "PidTagLocalCommitTime",					"Local commit time" },
	{ 0x670a, 0x0040, "PR_LOCAL_COMMIT_TIME_MAX",					"" },
	{ 0x670b, 0x0003, "PR_DELETED_COUNT_TOTAL",					"Total deleted item count" },
	{ 0x670c, 0x0048, "PR_AUTO_RESET",						"" },
	{ 0x6710, 0x0003, "PR_URL_COMP_NAME_HASH",					"" },
	{ 0x6711, 0x0003, "PR_MSG_FOLDER_TEMPLATE_RES_2",				"" },
	{ 0x6712, 0x0003, "PR_RANK",							"" },
	{ 0x6713, 0x000b, "PR_MSG_FOLDER_TEMPLATE_RES_4",				"" },
	{ 0x6714, 0x000b, "PR_MSG_FOLDER_TEMPLATE_RES_5",				"" },
	{ 0x6715, 0x000b, "PR_MSG_FOLDER_TEMPLATE_RES_6",				"" },
	{ 0x6716, 0x0102, "PR_MSG_FOLDER_TEMPLATE_RES_7",				"" },
	{ 0x6717, 0x0102, "PR_MSG_FOLDER_TEMPLATE_RES_8",				"" },
	{ 0x6718, 0x0102, "PR_MSG_FOLDER_TEMPLATE_RES_9",				"" },
	{ 0x6719, 0x001e, "PR_MSG_FOLDER_TEMPLATE_RES_10",				"" },
	{ 0x671a, 0x001e, "PR_MSG_FOLDER_TEMPLATE_RES_11",				"" },
	{ 0x671b, 0x001e, "PR_MSG_FOLDER_TEMPLATE_RES_12",				"" },
	{ 0x671e, 0x000b, "PR_PF_PLATINUM_HOME_MDB",					"" },
	{ 0x671f, 0x000b, "PR_PF_PROXY_REQUIRED",					"" },
	{ 0x6720, 0x0102, "PR_INTERNET_FREE_DOC_INFO",					"" },
	{ 0x6721, 0x0003, "PR_PF_OVER_HARD_QUOTA_LIMIT",				"" },
	{ 0x6722, 0x0003, "PR_PF_MSG_SIZE_LIMIT",					"" },
	{ 0x6743, 0x0003, "PR_CONNECTION_MODULUS",					"" },
	{ 0x6743, 0x0014, "PR_CONNECTION_MODULUS_EXTENDED",				"" },
	{ 0x6744, 0x001e, "PR_DELIVER_TO_DN",						"" },
	{ 0x6746, 0x0003, "PR_MIME_SIZE",						"" },
	{ 0x6747, 0x0014, "PR_FILE_SIZE_EXTENDED",					"" },
	{ 0x6748, 0x0014, "PidTagFolderId",						"Folder identifier" },
	{ 0x6749, 0x0014, "PidTagParentFolderId",					"Parent folder identifier" },
	{ 0x674a, 0x0014, "PidTagMid",							"Message identifier" },
	{ 0x674b, 0x0014, "PR_CATEG_ID",						"Exchange category identifier" },
	{ 0x674c, 0x0014, "PR_PARENT_CATEG_ID",						"Exchange parent category identifier" },
	{ 0x674d, 0x0014, "PR_INST_ID",							"" },
	{ 0x674e, 0x0003, "PR_INSTANCE_NUM",						"" },
	{ 0x674f, 0x0014, "PR_ADDRBOOK_MID",						"" },
	{ 0x6750, 0x0003, "PR_ICS_NOTIF",						"" },
	{ 0x6751, 0x0003, "PR_ARTICLE_NUM_NEXT",					"" },
	{ 0x6752, 0x0003, "PR_IMAP_LAST_ARTICLE_ID",					"" },
	{ 0x6753, 0x000b, "PR_NOT_822_RENDERABLE",					"" },
	{ 0x6758, 0x0102, "PR_LTID",							"" },
	{ 0x6759, 0x0102, "PR_CN_EXPORT",						"" },
	{ 0x675a, 0x0102, "PR_PCL_EXPORT",						"" },
	{ 0x675b, 0x1102, "PR_CN_MV_EXPORT",						"" },

	{ 0x6764, 0x0014, "",								"Exchange mailbox identifier" },

	{ 0x6770, 0x0003, "PidTagPstConfigurationFlags",				"Personal storage table configuration flags" },

	{ 0x6772, 0x0003, "PidTagPstSubtreeContainer",					"" },
	{ 0x6779, 0x0003, "PR_PF_QUOTA_STYLE",						"" },
	{ 0x677b, 0x0003, "PR_PF_STORAGE_QUOTA",					"" },
	{ 0x6783, 0x0003, "PR_SEARCH_FLAGS",						"" },
	{ 0x6783, 0x0102, "PR_USER_SID",						"" },

	{ 0x6796, 0x0102, "PidTagCnsetSeen",						"Seen synchronization change number set" },

	{ 0x67a4, 0x0014, "PidTagChangeNumber",						"Synchronization change number" },

	{ 0x67aa, 0x000b, "PR_ASSOCIATED",						"" },

	{ 0x67da, 0x0102, "PidTagCnsetSeenFAI",						"Seen folder associated information synchronization change number set" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The secure property type (0x67f0 - 0x67ff)
 */
libfmapi_property_type_t libfmapi_secure_property_types[ ] = {
	{ 0x67f0, 0x0102, "PR_PROFILE_SECURE_MAILBOX",					"" },
	{ 0x67f1, 0x0003, "PidTagLtpParentNid",						"Parent node identifier" },
	{ 0x67f2, 0x0003, "PidTagLtpRowId",						"Row identifier" },
	{ 0x67f3, 0x0003, "PidTagLtpRowVer",						"Row version" },
	{ 0x67f4, 0x0014, "PRQ_ID_SECURE4",						"" },
	{ 0x67ff, 0x0003, "PidTagPstPassword",						"Password checksum" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The custom message content property type (0x6800 - 0x7bff)
 */
libfmapi_property_type_t libfmapi_custom_message_content_property_types[ ] = {
	{ 0x6800, 0x001e, "PidTagOfflineAddressBookName",				"Offline address book name" },
	{ 0x6801, 0x0040, "PR_MAILBEAT_REQUEST_SENT",					"" },
	{ 0x6802, 0x001e, "PR_USENET_SITE_NAME",					"" },
	{ 0x6803, 0x000b, "PidTagSendOutlookRecallReport",				"Send recall report" },
	{ 0x6803, 0x0040, "PR_MAILBEAT_REQUEST_RECEIVED",				"" },
	{ 0x6804, 0x0040, "PR_MAILBEAT_REQUEST_PROCESSED",				"" },
	{ 0x6805, 0x0003, "PR_SHUTOFFQUOTA",						"" },
	{ 0x6805, 0x1003, "PidTagOfflineAddressBookTruncatedProperties",		"Offline address book truncated properties" },
	{ 0x6806, 0x0040, "PR_MAILBEAT_REPLY_SENT",					"" },
	{ 0x6807, 0x0040, "PR_MAILBEAT_REPLY_SUBMIT",					"" },
	{ 0x6808, 0x0003, "PidTagOfflineAddressBookFileType",				"Offline Address Book file type" },
	{ 0x6808, 0x0040, "PR_MAILBEAT_REPLY_RECEIVED",					"" },
	{ 0x6809, 0x0040, "PR_MAILBEAT_REPLY_PROCESSED",				"" },

	{ 0x682f, 0x001e, "PidTagMapiFormComposeCommand",				"View class" },

	{ 0x6833, 0x0048, "PR_VIEW_CLSID",						"View class identifier" },
	{ 0x6834, 0x0003, "PR_VIEW_STYLE",						"View style" },
	{ 0x6835, 0x0102, "",								"Binary view data" },
	{ 0x683a, 0x0003, "PR_VIEW_MAJORVERSION",					"View major version" },
	{ 0x683c, 0x0102, "",								"XML view data" },

	{ 0x6841, 0x0003, "PR_SCHDINFO_RESOURCE_TYPE",					"" },
	{ 0x6842, 0x0102, "PidTagSearchFolderId",					"Search folder identifier" },
	{ 0x6844, 0x101e, "PR_DELEGATES_DISPLAY_NAMES",					"" },
	{ 0x6845, 0x0102, "PR_DELEGATES_ENTRYID",					"" },
	{ 0x6845, 0x1102, "PR_DELEGATES_ENTRYIDS",					"" },
	{ 0x6847, 0x0003, "PR_FREEBUSY_START_RANGE",					"" },
	{ 0x6848, 0x0003, "PidTagSearchFolderEfpFlags",					"Extended search folder flags" },
	{ 0x6849, 0x001e, "PR_FREEBUSY_EMAIL_ADDRESS",					"" },
	{ 0x684f, 0x1003, "PR_FREEBUSY_ALL_MONTHS",					"" },
	{ 0x6850, 0x1102, "PR_FREEBUSY_ALL_EVENTS",					"" },
	{ 0x6851, 0x1003, "PR_FREEBUSY_TENTATIVE_MONTHS",				"" },
	{ 0x6852, 0x1102, "PR_FREEBUSY_TENTATIVE_EVENTS",				"" },
	{ 0x6853, 0x1003, "PR_FREEBUSY_BUSY_MONTHS",					"" },
	{ 0x6854, 0x1102, "PR_FREEBUSY_BUSY_EVENTS",					"" },
	{ 0x6855, 0x1003, "PR_FREEBUSY_OOF_MONTHS",					"" },
	{ 0x6856, 0x1102, "PR_FREEBUSY_OOF_EVENTS",					"" },
	{ 0x6868, 0x0040, "PR_FREEBUSY_LAST_MODIFIED",					"" },
	{ 0x6869, 0x0003, "PR_FREEBUSY_NUM_MONTHS",					"" },
	{ 0x686b, 0x1003, "PR_DELEGATES_SEE_PRIVATE",					"" },
	{ 0x686c, 0x0102, "PR_PERSONAL_FREEBUSY",					"" },
	{ 0x686d, 0x000b, "PR_PROCESS_MEETING_REQUESTS",				"" },
	{ 0x686e, 0x000b, "PR_DECLINE_RECURRING_MEETING_REQUESTS",			"" },
	{ 0x686f, 0x000b, "PR_DECLINE_CONFLICTING_MEETING_REQUESTS",			"" },
	{ 0x7001, 0x0102, "PR_VD_BINARY",						"" },
	{ 0x7002, 0x001e, "PR_VD_STRINGS",						"" },
	{ 0x7003, 0x0003, "PR_VD_FLAGS",						"" },
	{ 0x7004, 0x0102, "PR_VD_LINK_TO",						"" },
	{ 0x7005, 0x0102, "PR_VD_VIEW_FOLDER",						"" },
	{ 0x7006, 0x001e, "PR_VD_NAME",							"" },
	{ 0x7007, 0x0003, "PR_VD_VERSION",						"" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The custom message non-transmittable property type (0x7c00 - 0x7fff)
 */
libfmapi_property_type_t libfmapi_custom_message_non_transmittable_property_types[ ] = {
	{ 0x7c00, 0x001e, "PR_FAV_DISPLAY_NAME",					"" },
	{ 0x7c02, 0x0102, "PR_FAV_PUBLIC_SOURCE_KEY",					"" },
	{ 0x7c04, 0x0102, "PR_OST_OSTID",						"Offline storage table identifier" },
	{ 0x7c0a, 0x000b, "PR_STORE_SLOWLINK",						"" },
	{ 0x7d01, 0x0003, "PR_FAV_AUTOSUBFOLDERS",					"" },
	{ 0x7d01, 0x000b, "PR_PROCESSED",						"" },
	{ 0x7d02, 0x0102, "PR_FAV_PARENT_SOURCE_KEY",					"" },
	{ 0x7d03, 0x0003, "PR_FAV_LEVEL_MASK",						"" },
	{ 0x7d07, 0x0003, "PR_FAV_INHERIT_AUTO",					"" },
	{ 0x7d08, 0x0102, "PR_FAV_DEL_SUBS",						"" },
	{ 0x7ffa, 0x0003, "PR_ATTACHMENT_LINKID",					"Attachment link identifier" },
	{ 0x7ffb, 0x0040, "PR_EXCEPTION_STARTTIME",					"Exception start time" },
	{ 0x7ffc, 0x0040, "PR_EXCEPTION_ENDTIME",					"Exception end time" },
	{ 0x7ffd, 0x0003, "PR_ATTACHMENT_FLAGS",					"Attachment flags" },
	{ 0x7ffe, 0x000b, "PR_ATTACHMENT_HIDDEN",					"Hidden attachment" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The custom named property type (0x8000 - 0xffff)
 */
libfmapi_property_type_t libfmapi_custom_named_property_types[ ] = {
	{ 0x8001, 0x000b, "PR_EMS_AB_DISPLAY_NAME_OVERRIDE",				"" },
	{ 0x8003, 0x1102, "PR_EMS_AB_CA_CERTIFICATE",					"" },
	{ 0x8004, 0x001e, "PR_EMS_AB_FOLDER_PATHNAME",					"" },
	{ 0x8005, 0x000d, "PR_EMS_AB_MANAGER",						"" },
	{ 0x8005, 0x001e, "PR_EMS_AB_MANAGER_T",					"" },
	{ 0x8006, 0x000d, "PR_EMS_AB_HOME_MDB_O",					"" },
	{ 0x8006, 0x001e, "PR_EMS_AB_HOME_MDB",						"" },
	{ 0x8007, 0x000d, "PR_EMS_AB_HOME_MTA_O",					"" },
	{ 0x8007, 0x001e, "PR_EMS_AB_HOME_MTA",						"" },
	{ 0x8008, 0x000d, "PR_EMS_AB_IS_MEMBER_OF_DL",					"" },
	{ 0x8008, 0x001e, "PR_EMS_AB_IS_MEMBER_OF_DL_T",				"" },
	{ 0x8009, 0x000d, "PR_EMS_AB_MEMBER",						"" },
	{ 0x8009, 0x001e, "PR_EMS_AB_MEMBER_T",						"" },
	{ 0x800a, 0x001e, "PR_EMS_AB_AUTOREPLY_MESSAGE",				"" },
	{ 0x800b, 0x000b, "PR_EMS_AB_AUTOREPLY",					"" },
	{ 0x800c, 0x000d, "PR_EMS_AB_OWNER_O",						"" },
	{ 0x800c, 0x001e, "PR_EMS_AB_OWNER",						"" },
	{ 0x800d, 0x000d, "PR_EMS_AB_KM_SERVER_O",					"" },
	{ 0x800d, 0x001e, "PR_EMS_AB_KM_SERVER",					"" },
	{ 0x800e, 0x000d, "PidTagAddressBookReports",					"Address book reports" },
	{ 0x800f, 0x101e, "PidTagAddressBookProxyAddresses",				"Address book proxy addresses" },
	{ 0x8010, 0x0102, "PR_EMS_AB_HELP_DATA32",					"" },
	{ 0x8011, 0x001e, "PR_EMS_AB_TARGET_ADDRESS",					"" },
	{ 0x8012, 0x101e, "PR_EMS_AB_TELEPHONE_NUMBER",					"" },
	{ 0x8013, 0x0102, "PR_EMS_AB_NT_SECURITY_DESCRIPTOR",				"" },
	{ 0x8014, 0x000d, "PR_EMS_AB_HOME_MDB_BL_O",					"" },
	{ 0x8014, 0x101e, "PR_EMS_AB_HOME_MDB_BL",					"" },
	{ 0x8015, 0x000d, "PR_EMS_AB_PUBLIC_DELEGATES",					"" },
	{ 0x8015, 0x001e, "PR_EMS_AB_PUBLIC_DELEGATES_T",				"" },
	{ 0x8016, 0x0102, "PR_EMS_AB_CERTIFICATE_REVOCATION_LIST",			"" },
	{ 0x8017, 0x0102, "PR_EMS_AB_ADDRESS_ENTRY_DISPLAY_TABLE",			"" },
	{ 0x8018, 0x0102, "PR_EMS_AB_ADDRESS_SYNTAX",					"" },

	{ 0x8023, 0x0102, "PR_EMS_AB_BUSINESS_ROLES",					"" },
	{ 0x8024, 0x000d, "PR_EMS_AB_OWNER_BL_O",					"" },
	{ 0x8024, 0x101e, "PR_EMS_AB_OWNER_BL",						"" },
	{ 0x8025, 0x1102, "PR_EMS_AB_CROSS_CERTIFICATE_PAIR",				"" },
	{ 0x8026, 0x1102, "PR_EMS_AB_AUTHORITY_REVOCATION_LIST",			"" },
	{ 0x8027, 0x0102, "PR_EMS_AB_ASSOC_NT_ACCOUNT",					"" },
	{ 0x8028, 0x0040, "PR_EMS_AB_EXPIRATION_TIME",					"" },
	{ 0x8029, 0x0003, "PR_EMS_AB_USN_CHANGED",					"" },
	{ 0x802d, 0x001e, "PR_EMS_AB_EXTENSION_ATTRIBUTE_1",				"" },
	{ 0x802e, 0x001e, "PR_EMS_AB_EXTENSION_ATTRIBUTE_2",				"" },
	{ 0x802f, 0x001e, "PR_EMS_AB_EXTENSION_ATTRIBUTE_3",				"" },

	{ 0x8030, 0x001e, "PR_EMS_AB_EXTENSION_ATTRIBUTE_4",				"" },
	{ 0x8031, 0x001e, "PR_EMS_AB_EXTENSION_ATTRIBUTE_5",				"" },
	{ 0x8032, 0x001e, "PR_EMS_AB_EXTENSION_ATTRIBUTE_6",				"" },
	{ 0x8033, 0x001e, "PR_EMS_AB_EXTENSION_ATTRIBUTE_7",				"" },
	{ 0x8034, 0x001e, "PR_EMS_AB_EXTENSION_ATTRIBUTE_8",				"" },
	{ 0x8035, 0x001e, "PR_EMS_AB_EXTENSION_ATTRIBUTE_9",				"" },
	{ 0x8036, 0x001e, "PR_EMS_AB_EXTENSION_ATTRIBUTE_10",				"" },
	{ 0x8037, 0x1102, "PR_EMS_AB_SECURITY_PROTOCOL",				"" },
	{ 0x8038, 0x000d, "PR_EMS_AB_PF_CONTACTS_O",					"" },
	{ 0x8038, 0x101e, "PR_EMS_AB_PF_CONTACTS",					"" },
	{ 0x803a, 0x0102, "PR_EMS_AB_HELP_DATA16",					"" },
	{ 0x803b, 0x001e, "PR_EMS_AB_HELP_FILE_NAME",					"" },
	{ 0x803c, 0x000d, "PR_EMS_AB_OBJ_DIST_NAME_O",					"" },
	{ 0x803c, 0x001e, "PidTagAddressBookObjectDistinguishedName",			"Address book object distinguished name" },
	{ 0x803d, 0x001e, "PR_EMS_AB_ENCRYPT_ALG_SELECTED_OTHER",			"" },
	{ 0x803e, 0x001e, "PR_EMS_AB_AUTOREPLY_SUBJECT",				"" },
	{ 0x803f, 0x000d, "PR_EMS_AB_HOME_PUBLIC_SERVER_O",				"" },
	{ 0x803f, 0x001e, "PR_EMS_AB_HOME_PUBLIC_SERVER",				"" },
	{ 0x8040, 0x101e, "PR_EMS_AB_ENCRYPT_ALG_LIST_NA",				"" },
	{ 0x8041, 0x101e, "PR_EMS_AB_ENCRYPT_ALG_LIST_OTHER",				"" },
	{ 0x8042, 0x001e, "PR_EMS_AB_IMPORTED_FROM",					"" },
	{ 0x8043, 0x001e, "PR_EMS_AB_ENCRYPT_ALG_SELECTED_NA",				"" },
	{ 0x8044, 0x0003, "PR_EMS_AB_ACCESS_CATEGORY",					"" },
	{ 0x8045, 0x0102, "PR_EMS_AB_ACTIVATION_SCHEDULE",				"" },
	{ 0x8046, 0x0003, "PR_EMS_AB_ACTIVATION_STYLE",					"" },
	{ 0x8047, 0x0102, "PR_EMS_AB_ADDRESS_ENTRY_DISPLAY_TABLE_MSDOS",		"" },
	{ 0x8048, 0x001e, "PR_EMS_AB_ADDRESS_TYPE",					"" },
	{ 0x8049, 0x001e, "PR_EMS_AB_ADMD",						"" },
	{ 0x804a, 0x001e, "PR_EMS_AB_ADMIN_DESCRIPTION",				"" },
	{ 0x804b, 0x001e, "PR_EMS_AB_ADMIN_DISPLAY_NAME",				"" },
	{ 0x804c, 0x001e, "PR_EMS_AB_ADMIN_EXTENSION_DLL",				"" },
	{ 0x804d, 0x000d, "PR_EMS_AB_ALIASED_OBJECT_NAME_O",				"" },
	{ 0x804d, 0x001e, "PR_EMS_AB_ALIASED_OBJECT_NAME",				"" },
	{ 0x804e, 0x000d, "PR_EMS_AB_ALT_RECIPIENT_O",					"" },
	{ 0x804e, 0x001e, "PR_EMS_AB_ALT_RECIPIENT",					"" },
	{ 0x804f, 0x000d, "PR_EMS_AB_ALT_RECIPIENT_BL_O",				"" },
	{ 0x804f, 0x101e, "PR_EMS_AB_ALT_RECIPIENT_BL",					"" },
	{ 0x8050, 0x0102, "PR_EMS_AB_ANCESTOR_ID",					"" },
	{ 0x8051, 0x000d, "PR_EMS_AB_ASSOC_REMOTE_DXA_O",				"" },
	{ 0x8051, 0x101e, "PR_EMS_AB_ASSOC_REMOTE_DXA",					"" },
	{ 0x8052, 0x0003, "PR_EMS_AB_ASSOCIATION_LIFETIME",				"" },
	{ 0x8053, 0x000d, "PR_EMS_AB_AUTH_ORIG_BL_O",					"" },
	{ 0x8053, 0x101e, "PR_EMS_AB_AUTH_ORIG_BL",					"" },
	{ 0x8054, 0x001e, "PR_EMS_AB_AUTHORIZED_DOMAIN",				"" },
	{ 0x8055, 0x0102, "PR_EMS_AB_AUTHORIZED_PASSWORD",				"" },
	{ 0x8056, 0x001e, "PR_EMS_AB_AUTHORIZED_USER",					"" },
	{ 0x8057, 0x101e, "PR_EMS_AB_BUSINESS_CATEGORY",				"" },
	{ 0x8058, 0x000d, "PR_EMS_AB_CAN_CREATE_PF_O",					"" },
	{ 0x8058, 0x101e, "PR_EMS_AB_CAN_CREATE_PF",					"" },
	{ 0x8059, 0x000d, "PR_EMS_AB_CAN_CREATE_PF_BL_O",				"" },
	{ 0x8059, 0x101e, "PR_EMS_AB_CAN_CREATE_PF_BL",					"" },
	{ 0x805a, 0x000d, "PR_EMS_AB_CAN_CREATE_PF_DL_O",				"" },
	{ 0x805a, 0x101e, "PR_EMS_AB_CAN_CREATE_PF_DL",					"" },
	{ 0x805b, 0x000d, "PR_EMS_AB_CAN_CREATE_PF_DL_BL_O",				"" },
	{ 0x805b, 0x101e, "PR_EMS_AB_CAN_CREATE_PF_DL_BL",				"" },
	{ 0x805c, 0x000d, "PR_EMS_AB_CAN_NOT_CREATE_PF_O",				"" },
	{ 0x805c, 0x101e, "PR_EMS_AB_CAN_NOT_CREATE_PF",				"" },
	{ 0x805d, 0x000d, "PR_EMS_AB_CAN_NOT_CREATE_PF_BL_O",				"" },
	{ 0x805d, 0x101e, "PR_EMS_AB_CAN_NOT_CREATE_PF_BL",				"" },
	{ 0x805e, 0x000d, "PR_EMS_AB_CAN_NOT_CREATE_PF_DL_O",				"" },
	{ 0x805e, 0x101e, "PR_EMS_AB_CAN_NOT_CREATE_PF_DL",				"" },
	{ 0x805f, 0x000d, "PR_EMS_AB_CAN_NOT_CREATE_PF_DL_BL_O",			"" },
	{ 0x805f, 0x101e, "PR_EMS_AB_CAN_NOT_CREATE_PF_DL_BL",				"" },
	{ 0x8060, 0x000b, "PR_EMS_AB_CAN_PRESERVE_DNS",					"" },
	{ 0x8061, 0x0003, "PR_EMS_AB_CLOCK_ALERT_OFFSET",				"" },
	{ 0x8062, 0x000b, "PR_EMS_AB_CLOCK_ALERT_REPAIR",				"" },
	{ 0x8063, 0x0003, "PR_EMS_AB_CLOCK_WARNING_OFFSET",				"" },
	{ 0x8064, 0x000b, "PR_EMS_AB_CLOCK_WARNING_REPAIR",				"" },
	{ 0x8065, 0x001e, "PR_EMS_AB_COMPUTER_NAME",					"" },
	{ 0x8066, 0x101e, "PR_EMS_AB_CONNECTED_DOMAINS",				"" },
	{ 0x8067, 0x0003, "PR_EMS_AB_CONTAINER_INFO",					"" },
	{ 0x8068, 0x0003, "PR_EMS_AB_COST",						"" },
	{ 0x8069, 0x001e, "PR_EMS_AB_COUNTRY_NAME",					"" },
	{ 0x806a, 0x0003, "PR_EMS_AB_DELIV_CONT_LENGTH",				"" },
	{ 0x806b, 0x1102, "PR_EMS_AB_DELIV_EITS",					"" },
	{ 0x806c, 0x1102, "PR_EMS_AB_DELIV_EXT_CONT_TYPES",				"" },
	{ 0x806d, 0x000b, "PR_EMS_AB_DELIVER_AND_REDIRECT",				"" },
	{ 0x806e, 0x0003, "PR_EMS_AB_DELIVERY_MECHANISM",				"" },
	{ 0x806f, 0x101e, "PR_EMS_AB_DESCRIPTION",					"" },
	{ 0x8070, 0x101e, "PR_EMS_AB_DESTINATION_INDICATOR",				"" },
	{ 0x8071, 0x001e, "PR_EMS_AB_DIAGNOSTIC_REG_KEY",				"" },
	{ 0x8072, 0x000d, "PR_EMS_AB_DL_MEM_REJECT_PERMS_BL_O",				"" },
	{ 0x8072, 0x101e, "PR_EMS_AB_DL_MEM_REJECT_PERMS_BL",				"" },
	{ 0x8073, 0x000d, "PR_EMS_AB_DL_MEM_SUBMIT_PERMS_BL_O",				"" },
	{ 0x8073, 0x101e, "PR_EMS_AB_DL_MEM_SUBMIT_PERMS_BL",				"" },
	{ 0x8074, 0x1102, "PR_EMS_AB_DL_MEMBER_RULE",					"" },
	{ 0x8075, 0x000d, "PR_EMS_AB_DOMAIN_DEF_ALT_RECIP_O",				"" },
	{ 0x8075, 0x001e, "PR_EMS_AB_DOMAIN_DEF_ALT_RECIP",				"" },
	{ 0x8076, 0x001e, "PR_EMS_AB_DOMAIN_NAME",					"" },
	{ 0x8077, 0x0102, "PR_EMS_AB_DSA_SIGNATURE",					"" },
	{ 0x8078, 0x000b, "PR_EMS_AB_DXA_ADMIN_COPY",					"" },
	{ 0x8079, 0x000b, "PR_EMS_AB_DXA_ADMIN_FORWARD",				"" },
	{ 0x807a, 0x0003, "PR_EMS_AB_DXA_ADMIN_UPDATE",					"" },
	{ 0x807b, 0x000b, "PR_EMS_AB_DXA_APPEND_REQCN",					"" },
	{ 0x807c, 0x000d, "PR_EMS_AB_DXA_CONF_CONTAINER_LIST_O",			"" },
	{ 0x807c, 0x101e, "PR_EMS_AB_DXA_CONF_CONTAINER_LIST",				"" },
	{ 0x807d, 0x0040, "PR_EMS_AB_DXA_CONF_REQ_TIME",				"" },
	{ 0x807e, 0x001e, "PR_EMS_AB_DXA_CONF_SEQ",					"" },
	{ 0x807f, 0x0003, "PR_EMS_AB_DXA_CONF_SEQ_USN",					"" },
	{ 0x8080, 0x0003, "PR_EMS_AB_DXA_EXCHANGE_OPTIONS",				"" },
	{ 0x8081, 0x000b, "PR_EMS_AB_DXA_EXPORT_NOW",					"" },
	{ 0x8082, 0x0003, "PR_EMS_AB_DXA_FLAGS",					"" },
	{ 0x8083, 0x001e, "PR_EMS_AB_DXA_IMP_SEQ",					"" },
	{ 0x8084, 0x0040, "PR_EMS_AB_DXA_IMP_SEQ_TIME",					"" },
	{ 0x8085, 0x0003, "PR_EMS_AB_DXA_IMP_SEQ_USN",					"" },
	{ 0x8086, 0x000b, "PR_EMS_AB_DXA_IMPORT_NOW",					"" },
	{ 0x8087, 0x101e, "PR_EMS_AB_DXA_IN_TEMPLATE_MAP",				"" },
	{ 0x8088, 0x000d, "PR_EMS_AB_DXA_LOCAL_ADMIN_O",				"" },
	{ 0x8088, 0x001e, "PR_EMS_AB_DXA_LOCAL_ADMIN",					"" },
	{ 0x8089, 0x0003, "PR_EMS_AB_DXA_LOGGING_LEVEL",				"" },
	{ 0x808a, 0x001e, "PR_EMS_AB_DXA_NATIVE_ADDRESS_TYPE",				"" },
	{ 0x808b, 0x101e, "PR_EMS_AB_DXA_OUT_TEMPLATE_MAP",				"" },
	{ 0x808c, 0x001e, "PR_EMS_AB_DXA_PASSWORD",					"" },
	{ 0x808d, 0x0003, "PR_EMS_AB_DXA_PREV_EXCHANGE_OPTIONS",			"" },
	{ 0x808e, 0x000b, "PR_EMS_AB_DXA_PREV_EXPORT_NATIVE_ONLY",			"" },
	{ 0x808f, 0x0003, "PR_EMS_AB_DXA_PREV_IN_EXCHANGE_SENSITIVITY",			"" },
	{ 0x8090, 0x000d, "PR_EMS_AB_DXA_PREV_REMOTE_ENTRIES_O",			"" },
	{ 0x8090, 0x001e, "PR_EMS_AB_DXA_PREV_REMOTE_ENTRIES",				"" },
	{ 0x8091, 0x0003, "PR_EMS_AB_DXA_PREV_REPLICATION_SENSITIVITY",			"" },
	{ 0x8092, 0x0003, "PR_EMS_AB_DXA_PREV_TEMPLATE_OPTIONS",			"" },
	{ 0x8093, 0x0003, "PR_EMS_AB_DXA_PREV_TYPES",					"" },
	{ 0x8094, 0x001e, "PR_EMS_AB_DXA_RECIPIENT_CP",					"" },
	{ 0x8095, 0x000d, "PR_EMS_AB_DXA_REMOTE_CLIENT_O",				"" },
	{ 0x8095, 0x001e, "PR_EMS_AB_DXA_REMOTE_CLIENT",				"" },
	{ 0x8096, 0x001e, "PR_EMS_AB_DXA_REQ_SEQ",					"" },
	{ 0x8097, 0x0040, "PR_EMS_AB_DXA_REQ_SEQ_TIME",					"" },
	{ 0x8098, 0x0003, "PR_EMS_AB_DXA_REQ_SEQ_USN",					"" },
	{ 0x8099, 0x001e, "PR_EMS_AB_DXA_REQNAME",					"" },
	{ 0x809a, 0x001e, "PR_EMS_AB_DXA_SVR_SEQ",					"" },
	{ 0x809b, 0x0040, "PR_EMS_AB_DXA_SVR_SEQ_TIME",					"" },
	{ 0x809c, 0x0003, "PR_EMS_AB_DXA_SVR_SEQ_USN",					"" },
	{ 0x809d, 0x0003, "PR_EMS_AB_DXA_TASK",						"" },
	{ 0x809e, 0x0003, "PR_EMS_AB_DXA_TEMPLATE_OPTIONS",				"" },
	{ 0x809f, 0x0040, "PR_EMS_AB_DXA_TEMPLATE_TIMESTAMP",				"" },
	{ 0x80a0, 0x0003, "PR_EMS_AB_DXA_TYPES",					"" },
	{ 0x80a1, 0x000d, "PR_EMS_AB_DXA_UNCONF_CONTAINER_LIST_O",			"" },
	{ 0x80a1, 0x101e, "PR_EMS_AB_DXA_UNCONF_CONTAINER_LIST",			"" },
	{ 0x80a2, 0x0003, "PR_EMS_AB_ENCAPSULATION_METHOD",				"" },
	{ 0x80a3, 0x000b, "PR_EMS_AB_ENCRYPT",						"" },
	{ 0x80a4, 0x000b, "PR_EMS_AB_EXPAND_DLS_LOCALLY",				"" },
	{ 0x80a5, 0x000d, "PR_EMS_AB_EXPORT_CONTAINERS_O",				"" },
	{ 0x80a5, 0x101e, "PR_EMS_AB_EXPORT_CONTAINERS",				"" },
	{ 0x80a6, 0x000b, "PR_EMS_AB_EXPORT_CUSTOM_RECIPIENTS",				"" },
	{ 0x80a7, 0x000b, "PR_EMS_AB_EXTENDED_CHARS_ALLOWED",				"" },
	{ 0x80a8, 0x1102, "PR_EMS_AB_EXTENSION_DATA",					"" },
	{ 0x80a9, 0x101e, "PR_EMS_AB_EXTENSION_NAME",					"" },
	{ 0x80aa, 0x101e, "PR_EMS_AB_EXTENSION_NAME_INHERITED",				"" },
	{ 0x80ab, 0x1102, "PR_EMS_AB_FACSIMILE_TELEPHONE_NUMBER",			"" },
	{ 0x80ac, 0x0102, "PR_EMS_AB_FILE_VERSION",					"" },
	{ 0x80ad, 0x000b, "PR_EMS_AB_FILTER_LOCAL_ADDRESSES",				"" },
	{ 0x80ae, 0x000d, "PR_EMS_AB_FOLDERS_CONTAINER_O",				"" },
	{ 0x80ae, 0x001e, "PR_EMS_AB_FOLDERS_CONTAINER",				"" },
	{ 0x80af, 0x0003, "PR_EMS_AB_GARBAGE_COLL_PERIOD",				"" },
	{ 0x80b0, 0x001e, "PR_EMS_AB_GATEWAY_LOCAL_CRED",				"" },
	{ 0x80b1, 0x001e, "PR_EMS_AB_GATEWAY_LOCAL_DESIG",				"" },
	{ 0x80b2, 0x101e, "PR_EMS_AB_GATEWAY_PROXY",					"" },
	{ 0x80b3, 0x0102, "PR_EMS_AB_GATEWAY_ROUTING_TREE",				"" },
	{ 0x80b4, 0x0040, "PR_EMS_AB_GWART_LAST_MODIFIED",				"" },
	{ 0x80b5, 0x000d, "PR_EMS_AB_HAS_FULL_REPLICA_NCS_O",				"" },
	{ 0x80b5, 0x101e, "PR_EMS_AB_HAS_FULL_REPLICA_NCS",				"" },
	{ 0x80b6, 0x000d, "PR_EMS_AB_HAS_MASTER_NCS_O",					"" },
	{ 0x80b6, 0x101e, "PR_EMS_AB_HAS_MASTER_NCS",					"" },
	{ 0x80b7, 0x0003, "PR_EMS_AB_HEURISTICS",					"" },
	{ 0x80b8, 0x000b, "PR_EMS_AB_HIDE_DL_MEMBERSHIP",				"" },
	{ 0x80b9, 0x000b, "PR_EMS_AB_HIDE_FROM_ADDRESS_BOOK",				"" },
	{ 0x80ba, 0x000d, "PR_EMS_AB_IMPORT_CONTAINER_O",				"" },
	{ 0x80ba, 0x001e, "PR_EMS_AB_IMPORT_CONTAINER",					"" },
	{ 0x80bb, 0x0003, "PR_EMS_AB_IMPORT_SENSITIVITY",				"" },
	{ 0x80bc, 0x000d, "PR_EMS_AB_INBOUND_SITES_O",					"" },
	{ 0x80bc, 0x101e, "PR_EMS_AB_INBOUND_SITES",					"" },
	{ 0x80bd, 0x0003, "PR_EMS_AB_INSTANCE_TYPE",					"" },
	{ 0x80be, 0x101e, "PR_EMS_AB_INTERNATIONAL_ISDN_NUMBER",			"" },
	{ 0x80bf, 0x0102, "PR_EMS_AB_INVOCATION_ID",					"" },
	{ 0x80c0, 0x000b, "PR_EMS_AB_IS_DELETED",					"" },
	{ 0x80c1, 0x000b, "PR_EMS_AB_IS_SINGLE_VALUED",					"" },
	{ 0x80c2, 0x1102, "PR_EMS_AB_KCC_STATUS",					"" },
	{ 0x80c3, 0x101e, "PR_EMS_AB_KNOWLEDGE_INFORMATION",				"" },
	{ 0x80c4, 0x0003, "PR_EMS_AB_LINE_WRAP",					"" },
	{ 0x80c5, 0x0003, "PR_EMS_AB_LINK_ID",						"" },
	{ 0x80c6, 0x001e, "PR_EMS_AB_LOCAL_BRIDGE_HEAD",				"" },
	{ 0x80c7, 0x001e, "PR_EMS_AB_LOCAL_BRIDGE_HEAD_ADDRESS",			"" },
	{ 0x80c8, 0x000b, "PR_EMS_AB_LOCAL_INITIAL_TURN",				"" },
	{ 0x80c9, 0x000d, "PR_EMS_AB_LOCAL_SCOPE_O",					"" },
	{ 0x80c9, 0x101e, "PR_EMS_AB_LOCAL_SCOPE",					"" },
	{ 0x80ca, 0x001e, "PR_EMS_AB_LOG_FILENAME",					"" },
	{ 0x80cb, 0x0003, "PR_EMS_AB_LOG_ROLLOVER_INTERVAL",				"" },
	{ 0x80cc, 0x000b, "PR_EMS_AB_MAINTAIN_AUTOREPLY_HISTORY",			"" },
	{ 0x80cd, 0x0003, "PR_EMS_AB_MAPI_DISPLAY_TYPE",				"" },
	{ 0x80ce, 0x0003, "PR_EMS_AB_MAPI_ID",						"" },
	{ 0x80cf, 0x0003, "PR_EMS_AB_MDB_BACKOFF_INTERVAL",				"" },
	{ 0x80d0, 0x0003, "PR_EMS_AB_MDB_MSG_TIME_OUT_PERIOD",				"" },
	{ 0x80d1, 0x0003, "PR_EMS_AB_MDB_OVER_QUOTA_LIMIT",				"" },
	{ 0x80d2, 0x0003, "PR_EMS_AB_MDB_STORAGE_QUOTA",				"" },
	{ 0x80d3, 0x0003, "PR_EMS_AB_MDB_UNREAD_LIMIT",					"" },
	{ 0x80d4, 0x000b, "PR_EMS_AB_MDB_USE_DEFAULTS",					"" },
	{ 0x80d5, 0x000b, "PR_EMS_AB_MESSAGE_TRACKING_ENABLED",				"" },
	{ 0x80d6, 0x000b, "PR_EMS_AB_MONITOR_CLOCK",					"" },
	{ 0x80d7, 0x000b, "PR_EMS_AB_MONITOR_SERVERS",					"" },
	{ 0x80d8, 0x000b, "PR_EMS_AB_MONITOR_SERVICES",					"" },
	{ 0x80d9, 0x000d, "PR_EMS_AB_MONITORED_CONFIGURATIONS_O",			"" },
	{ 0x80d9, 0x101e, "PR_EMS_AB_MONITORED_CONFIGURATIONS",				"" },
	{ 0x80da, 0x000d, "PR_EMS_AB_MONITORED_SERVERS_O",				"" },
	{ 0x80da, 0x101e, "PR_EMS_AB_MONITORED_SERVERS",				"" },
	{ 0x80db, 0x101e, "PR_EMS_AB_MONITORED_SERVICES",				"" },
	{ 0x80dc, 0x0003, "PR_EMS_AB_MONITORING_ALERT_DELAY",				"" },
	{ 0x80dd, 0x0003, "PR_EMS_AB_MONITORING_ALERT_UNITS",				"" },
	{ 0x80de, 0x0003, "PR_EMS_AB_MONITORING_AVAILABILITY_STYLE",			"" },
	{ 0x80df, 0x0102, "PR_EMS_AB_MONITORING_AVAILABILITY_WINDOW",			"" },
	{ 0x80e0, 0x000d, "PR_EMS_AB_MONITORING_CACHED_VIA_MAIL_O",			"" },
	{ 0x80e0, 0x101e, "PR_EMS_AB_MONITORING_CACHED_VIA_MAIL",			"" },
	{ 0x80e1, 0x000d, "PR_EMS_AB_MONITORING_CACHED_VIA_RPC_O",			"" },
	{ 0x80e1, 0x101e, "PR_EMS_AB_MONITORING_CACHED_VIA_RPC",			"" },
	{ 0x80e2, 0x1102, "PR_EMS_AB_MONITORING_ESCALATION_PROCEDURE",			"" },
	{ 0x80e3, 0x0003, "PR_EMS_AB_MONITORING_HOTSITE_POLL_INTERVAL",			"" },
	{ 0x80e4, 0x0003, "PR_EMS_AB_MONITORING_HOTSITE_POLL_UNITS",			"" },
	{ 0x80e5, 0x0003, "PR_EMS_AB_MONITORING_MAIL_UPDATE_INTERVAL",			"" },
	{ 0x80e6, 0x0003, "PR_EMS_AB_MONITORING_MAIL_UPDATE_UNITS",			"" },
	{ 0x80e7, 0x0003, "PR_EMS_AB_MONITORING_NORMAL_POLL_INTERVAL",			"" },
	{ 0x80e8, 0x0003, "PR_EMS_AB_MONITORING_NORMAL_POLL_UNITS",			"" },
	{ 0x80e9, 0x000d, "PR_EMS_AB_MONITORING_RECIPIENTS_O",				"" },
	{ 0x80e9, 0x101e, "PR_EMS_AB_MONITORING_RECIPIENTS",				"" },
	{ 0x80ea, 0x000d, "PR_EMS_AB_MONITORING_RECIPIENTS_NDR_O",			"" },
	{ 0x80ea, 0x101e, "PR_EMS_AB_MONITORING_RECIPIENTS_NDR",			"" },
	{ 0x80eb, 0x0003, "PR_EMS_AB_MONITORING_RPC_UPDATE_INTERVAL",			"" },
	{ 0x80ec, 0x0003, "PR_EMS_AB_MONITORING_RPC_UPDATE_UNITS",			"" },
	{ 0x80ed, 0x0003, "PR_EMS_AB_MONITORING_WARNING_DELAY",				"" },
	{ 0x80ee, 0x0003, "PR_EMS_AB_MONITORING_WARNING_UNITS",				"" },
	{ 0x80ef, 0x001e, "PR_EMS_AB_MTA_LOCAL_CRED",					"" },
	{ 0x80f0, 0x001e, "PR_EMS_AB_MTA_LOCAL_DESIG",					"" },
	{ 0x80f1, 0x0102, "PR_EMS_AB_N_ADDRESS",					"" },
	{ 0x80f2, 0x0003, "PR_EMS_AB_N_ADDRESS_TYPE",					"" },
	{ 0x80f3, 0x001e, "PR_EMS_AB_NT_MACHINE_NAME",					"" },
	{ 0x80f4, 0x0003, "PR_EMS_AB_NUM_OF_OPEN_RETRIES",				"" },
	{ 0x80f5, 0x0003, "PR_EMS_AB_NUM_OF_TRANSFER_RETRIES",				"" },
	{ 0x80f6, 0x0003, "PR_EMS_AB_OBJECT_CLASS_CATEGORY",				"" },
	{ 0x80f7, 0x0003, "PR_EMS_AB_OBJECT_VERSION",					"" },
	{ 0x80f8, 0x000d, "PR_EMS_AB_OFF_LINE_AB_CONTAINERS_O",				"" },
	{ 0x80f8, 0x101e, "PR_EMS_AB_OFF_LINE_AB_CONTAINERS",				"" },
	{ 0x80f9, 0x0102, "PR_EMS_AB_OFF_LINE_AB_SCHEDULE",				"" },
	{ 0x80fa, 0x000d, "PR_EMS_AB_OFF_LINE_AB_SERVER_O",				"" },
	{ 0x80fa, 0x001e, "PR_EMS_AB_OFF_LINE_AB_SERVER",				"" },
	{ 0x80fb, 0x0003, "PR_EMS_AB_OFF_LINE_AB_STYLE",				"" },
	{ 0x80fc, 0x0003, "PR_EMS_AB_OID_TYPE",						"" },
	{ 0x80fd, 0x0102, "PR_EMS_AB_OM_OBJECT_CLASS",					"" },
	{ 0x80fe, 0x0003, "PR_EMS_AB_OM_SYNTAX",					"" },
	{ 0x80ff, 0x000b, "PR_EMS_AB_OOF_REPLY_TO_ORIGINATOR",				"" },

	{ 0x8100, 0x0003, "PR_EMS_AB_OPEN_RETRY_INTERVAL",				"" },
	{ 0x8101, 0x101e, "PR_EMS_AB_ORGANIZATION_NAME",				"" },
	{ 0x8102, 0x101e, "PR_EMS_AB_ORGANIZATIONAL_UNIT_NAME",				"" },
	{ 0x8103, 0x0102, "PR_EMS_AB_ORIGINAL_DISPLAY_TABLE",				"" },
	{ 0x8104, 0x0102, "PR_EMS_AB_ORIGINAL_DISPLAY_TABLE_MSDOS",			"" },
	{ 0x8105, 0x000d, "PR_EMS_AB_OUTBOUND_SITES_O",					"" },
	{ 0x8105, 0x101e, "PR_EMS_AB_OUTBOUND_SITES",					"" },
	{ 0x8106, 0x0102, "PR_EMS_AB_P_SELECTOR",					"" },
	{ 0x8107, 0x0102, "PR_EMS_AB_P_SELECTOR_INBOUND",				"" },
	{ 0x8108, 0x0102, "PR_EMS_AB_PER_MSG_DIALOG_DISPLAY_TABLE",			"" },
	{ 0x8109, 0x0102, "PR_EMS_AB_PER_RECIP_DIALOG_DISPLAY_TABLE",			"" },
	{ 0x810a, 0x0102, "PR_EMS_AB_PERIOD_REP_SYNC_TIMES",				"" },
	{ 0x810b, 0x0003, "PR_EMS_AB_PERIOD_REPL_STAGGER",				"" },
	{ 0x810c, 0x1102, "PR_EMS_AB_POSTAL_ADDRESS",					"" },
	{ 0x810d, 0x1003, "PR_EMS_AB_PREFERRED_DELIVERY_METHOD",			"" },
	{ 0x810e, 0x001e, "PR_EMS_AB_PRMD",						"" },
	{ 0x810f, 0x001e, "PR_EMS_AB_PROXY_GENERATOR_DLL",				"" },
	{ 0x8110, 0x000d, "PR_EMS_AB_PUBLIC_DELEGATES_BL_O",				"" },
	{ 0x8110, 0x101e, "PR_EMS_AB_PUBLIC_DELEGATES_BL",				"" },
	{ 0x8111, 0x0102, "PR_EMS_AB_QUOTA_NOTIFICATION_SCHEDULE",			"" },
	{ 0x8112, 0x0003, "PR_EMS_AB_QUOTA_NOTIFICATION_STYLE",				"" },
	{ 0x8113, 0x0003, "PR_EMS_AB_RANGE_LOWER",					"" },
	{ 0x8114, 0x0003, "PR_EMS_AB_RANGE_UPPER",					"" },
	{ 0x8115, 0x001e, "PR_EMS_AB_RAS_CALLBACK_NUMBER",				"" },
	{ 0x8116, 0x001e, "PR_EMS_AB_RAS_PHONE_NUMBER",					"" },
	{ 0x8117, 0x001e, "PR_EMS_AB_RAS_PHONEBOOK_ENTRY_NAME",				"" },
	{ 0x8118, 0x001e, "PR_EMS_AB_RAS_REMOTE_SRVR_NAME",				"" },
	{ 0x8119, 0x001e, "PR_CE_SIGNATURE",						"Text signature" },
	{ 0x8119, 0x1102, "PR_EMS_AB_REGISTERED_ADDRESS",				"" },
	{ 0x811a, 0x001e, "PR_EMS_AB_REMOTE_BRIDGE_HEAD",				"" },
	{ 0x811b, 0x001e, "PR_EMS_AB_REMOTE_BRIDGE_HEAD_ADDRESS",			"" },
	{ 0x811c, 0x000d, "PR_EMS_AB_REMOTE_OUT_BH_SERVER_O",				"" },
	{ 0x811c, 0x001e, "PR_EMS_AB_REMOTE_OUT_BH_SERVER",				"" },
	{ 0x811d, 0x000d, "PR_EMS_AB_REMOTE_SITE_O",					"" },
	{ 0x811d, 0x001e, "PR_EMS_AB_REMOTE_SITE",					"" },
	{ 0x811e, 0x0003, "PR_EMS_AB_REPLICATION_SENSITIVITY",				"" },
	{ 0x811f, 0x0003, "PR_EMS_AB_REPLICATION_STAGGER",				"" },
	{ 0x8120, 0x000b, "PR_EMS_AB_REPORT_TO_ORIGINATOR",				"" },
	{ 0x8121, 0x000b, "PR_EMS_AB_REPORT_TO_OWNER",					"" },
	{ 0x8122, 0x0003, "PR_EMS_AB_REQ_SEQ",						"" },
	{ 0x8123, 0x000d, "PR_EMS_AB_RESPONSIBLE_LOCAL_DXA_O",				"" },
	{ 0x8123, 0x001e, "PR_EMS_AB_RESPONSIBLE_LOCAL_DXA",				"" },
	{ 0x8124, 0x000d, "PR_EMS_AB_RID_SERVER_O",					"" },
	{ 0x8124, 0x001e, "PR_EMS_AB_RID_SERVER",					"" },
	{ 0x8125, 0x000d, "PR_EMS_AB_ROLE_OCCUPANT_O",					"" },
	{ 0x8125, 0x101e, "PR_EMS_AB_ROLE_OCCUPANT",					"" },
	{ 0x8126, 0x101e, "PR_EMS_AB_ROUTING_LIST",					"" },
	{ 0x8127, 0x0003, "PR_EMS_AB_RTS_CHECKPOINT_SIZE",				"" },
	{ 0x8128, 0x0003, "PR_EMS_AB_RTS_RECOVERY_TIMEOUT",				"" },
	{ 0x8129, 0x0003, "PR_EMS_AB_RTS_WINDOW_SIZE",					"" },
	{ 0x812a, 0x000d, "PR_EMS_AB_RUNS_ON_O",					"" },
	{ 0x812a, 0x101e, "PR_EMS_AB_RUNS_ON",						"" },
	{ 0x812b, 0x0102, "PR_EMS_AB_S_SELECTOR",					"" },
	{ 0x812c, 0x0102, "PR_EMS_AB_S_SELECTOR_INBOUND",				"" },
	{ 0x812d, 0x0003, "PR_EMS_AB_SEARCH_FLAGS",					"" },
	{ 0x812e, 0x1102, "PR_EMS_AB_SEARCH_GUIDE",					"" },
	{ 0x812f, 0x000d, "PR_EMS_AB_SEE_ALSO_O",					"" },
	{ 0x812f, 0x101e, "PR_EMS_AB_SEE_ALSO",						"" },
	{ 0x8130, 0x101e, "PR_EMS_AB_SERIAL_NUMBER",					"" },
	{ 0x8131, 0x0003, "PR_EMS_AB_SERVICE_ACTION_FIRST",				"" },
	{ 0x8132, 0x0003, "PR_EMS_AB_SERVICE_ACTION_OTHER",				"" },
	{ 0x8133, 0x0003, "PR_EMS_AB_SERVICE_ACTION_SECOND",				"" },
	{ 0x8134, 0x0003, "PR_EMS_AB_SERVICE_RESTART_DELAY",				"" },
	{ 0x8135, 0x001e, "PR_EMS_AB_SERVICE_RESTART_MESSAGE",				"" },
	{ 0x8136, 0x0003, "PR_EMS_AB_SESSION_DISCONNECT_TIMER",				"" },
	{ 0x8137, 0x101e, "PR_EMS_AB_SITE_AFFINITY",					"" },
	{ 0x8138, 0x101e, "PR_EMS_AB_SITE_PROXY_SPACE",					"" },
	{ 0x8139, 0x0040, "PR_EMS_AB_SPACE_LAST_COMPUTED",				"" },
	{ 0x813a, 0x001e, "PR_EMS_AB_STREET_ADDRESS",					"" },
	{ 0x813b, 0x000d, "PR_EMS_AB_SUB_REFS_O",					"" },
	{ 0x813b, 0x101e, "PR_EMS_AB_SUB_REFS",						"" },
	{ 0x813c, 0x0003, "PR_EMS_AB_SUBMISSION_CONT_LENGTH",				"" },
	{ 0x813d, 0x1102, "PR_EMS_AB_SUPPORTED_APPLICATION_CONTEXT",			"" },
	{ 0x813e, 0x000d, "PR_EMS_AB_SUPPORTING_STACK_O",				"" },
	{ 0x813e, 0x101e, "PR_EMS_AB_SUPPORTING_STACK",					"" },
	{ 0x813f, 0x000d, "PR_EMS_AB_SUPPORTING_STACK_BL_O",				"" },
	{ 0x813f, 0x101e, "PR_EMS_AB_SUPPORTING_STACK_BL",				"" },
	{ 0x8140, 0x0102, "PR_EMS_AB_T_SELECTOR",					"" },
	{ 0x8141, 0x0102, "PR_EMS_AB_T_SELECTOR_INBOUND",				"" },
	{ 0x8142, 0x101e, "PR_EMS_AB_TARGET_MTAS",					"" },
	{ 0x8143, 0x1102, "PR_EMS_AB_TELETEX_TERMINAL_IDENTIFIER",			"" },
	{ 0x8144, 0x0003, "PR_EMS_AB_TEMP_ASSOC_THRESHOLD",				"" },
	{ 0x8145, 0x0003, "PR_EMS_AB_TOMBSTONE_LIFETIME",				"" },
	{ 0x8146, 0x001e, "PR_EMS_AB_TRACKING_LOG_PATH_NAME",				"" },
	{ 0x8147, 0x0003, "PR_EMS_AB_TRANS_RETRY_MINS",					"" },
	{ 0x8148, 0x0003, "PR_EMS_AB_TRANS_TIMEOUT_MINS",				"" },
	{ 0x8149, 0x0003, "PR_EMS_AB_TRANSFER_RETRY_INTERVAL",				"" },
	{ 0x814a, 0x0003, "PR_EMS_AB_TRANSFER_TIMEOUT_NON_URGENT",			"" },
	{ 0x814b, 0x0003, "PR_EMS_AB_TRANSFER_TIMEOUT_NORMAL",				"" },
	{ 0x814c, 0x0003, "PR_EMS_AB_TRANSFER_TIMEOUT_URGENT",				"" },
	{ 0x814d, 0x0003, "PR_EMS_AB_TRANSLATION_TABLE_USED",				"" },
	{ 0x814e, 0x000b, "PR_EMS_AB_TRANSPORT_EXPEDITED_DATA",				"" },
	{ 0x814f, 0x0003, "PR_EMS_AB_TRUST_LEVEL",					"" },
	{ 0x8150, 0x0003, "PR_EMS_AB_TURN_REQUEST_THRESHOLD",				"" },
	{ 0x8151, 0x000b, "PR_EMS_AB_TWO_WAY_ALTERNATE_FACILITY",			"" },
	{ 0x8152, 0x000d, "PR_EMS_AB_UNAUTH_ORIG_BL_O",					"" },
	{ 0x8152, 0x101e, "PR_EMS_AB_UNAUTH_ORIG_BL",					"" },
	{ 0x8153, 0x1102, "PR_EMS_AB_USER_PASSWORD",					"" },
	{ 0x8154, 0x0003, "PR_EMS_AB_USN_CREATED",					"" },
	{ 0x8155, 0x0003, "PR_EMS_AB_USN_DSA_LAST_OBJ_REMOVED",				"" },
	{ 0x8156, 0x0003, "PR_EMS_AB_USN_LAST_OBJ_REM",					"" },
	{ 0x8157, 0x0003, "PR_EMS_AB_USN_SOURCE",					"" },
	{ 0x8158, 0x101e, "PR_EMS_AB_X121_ADDRESS",					"" },
	{ 0x8159, 0x0102, "PR_EMS_AB_X25_CALL_USER_DATA_INCOMING",			"" },
	{ 0x815a, 0x0102, "PR_EMS_AB_X25_CALL_USER_DATA_OUTGOING",			"" },
	{ 0x815b, 0x0102, "PR_EMS_AB_X25_FACILITIES_DATA_INCOMING",			"" },
	{ 0x815c, 0x0102, "PR_EMS_AB_X25_FACILITIES_DATA_OUTGOING",			"" },
	{ 0x815d, 0x0102, "PR_EMS_AB_X25_LEASED_LINE_PORT",				"" },
	{ 0x815e, 0x000b, "PR_EMS_AB_X25_LEASED_OR_SWITCHED",				"" },
	{ 0x815f, 0x001e, "PR_EMS_AB_X25_REMOTE_MTA_PHONE",				"" },
	{ 0x8160, 0x0102, "PR_EMS_AB_X400_ATTACHMENT_TYPE",				"" },
	{ 0x8161, 0x0003, "PR_EMS_AB_X400_SELECTOR_SYNTAX",				"" },
	{ 0x8162, 0x0102, "PR_EMS_AB_X500_ACCESS_CONTROL_LIST",				"" },
	{ 0x8163, 0x0003, "PR_EMS_AB_XMIT_TIMEOUT_NON_URGENT",				"" },
	{ 0x8164, 0x0003, "PR_EMS_AB_XMIT_TIMEOUT_NORMAL",				"" },
	{ 0x8165, 0x0003, "PR_EMS_AB_XMIT_TIMEOUT_URGENT",				"" },
	{ 0x8166, 0x0102, "PR_EMS_AB_SITE_FOLDER_GUID",					"" },
	{ 0x8167, 0x000d, "PR_EMS_AB_SITE_FOLDER_SERVER_O",				"" },
	{ 0x8167, 0x001e, "PR_EMS_AB_SITE_FOLDER_SERVER",				"" },
	{ 0x8168, 0x0003, "PR_EMS_AB_REPLICATION_MAIL_MSG_SIZE",			"" },
	{ 0x8169, 0x0102, "PR_EMS_AB_MAXIMUM_OBJECT_ID",				"" },
	{ 0x8170, 0x101e, "PidTagAddressBookNetworkAddress",				"Address book network address" },
	{ 0x8171, 0x101e, "PR_EMS_AB_LDAP_DISPLAY_NAME",				"" },
	{ 0x8173, 0x0003, "PR_EMS_AB_SCHEMA_FLAGS",					"" },
	{ 0x8174, 0x000d, "PR_EMS_AB_BRIDGEHEAD_SERVERS_O",				"" },
	{ 0x8174, 0x101e, "PR_EMS_AB_BRIDGEHEAD_SERVERS",				"" },
	{ 0x8175, 0x001e, "PR_EMS_AB_WWW_HOME_PAGE",					"" },
	{ 0x8176, 0x001e, "PR_EMS_AB_NNTP_CONTENT_FORMAT",				"" },
	{ 0x8177, 0x001e, "PR_EMS_AB_POP_CONTENT_FORMAT",				"" },
	{ 0x8178, 0x0003, "PR_EMS_AB_LANGUAGE",						"" },
	{ 0x8179, 0x001e, "PR_EMS_AB_POP_CHARACTER_SET",				"" },
	{ 0x817a, 0x0003, "PR_EMS_AB_USN_INTERSITE",					"" },
	{ 0x817b, 0x001e, "PR_EMS_AB_SUB_SITE",						"" },
	{ 0x817c, 0x1003, "PR_EMS_AB_SCHEMA_VERSION",					"" },
	{ 0x817d, 0x001e, "PR_EMS_AB_NNTP_CHARACTER_SET",				"" },
	{ 0x817e, 0x000b, "PR_EMS_AB_USE_SERVER_VALUES",				"" },
	{ 0x817f, 0x0003, "PR_EMS_AB_ENABLED_PROTOCOLS",				"" },
	{ 0x8180, 0x0102, "PR_EMS_AB_CONNECTION_LIST_FILTER",				"" },
	{ 0x8181, 0x101e, "PR_EMS_AB_AVAILABLE_AUTHORIZATION_PACKAGES",			"" },
	{ 0x8182, 0x101e, "PR_EMS_AB_CHARACTER_SET_LIST",				"" },
	{ 0x8183, 0x000b, "PR_EMS_AB_USE_SITE_VALUES",					"" },
	{ 0x8184, 0x101e, "PR_EMS_AB_ENABLED_AUTHORIZATION_PACKAGES",			"" },
	{ 0x8185, 0x001e, "PR_EMS_AB_CHARACTER_SET",					"" },
	{ 0x8186, 0x0003, "PR_EMS_AB_CONTENT_TYPE",					"" },
	{ 0x8187, 0x000b, "PR_EMS_AB_ANONYMOUS_ACCESS",					"" },
	{ 0x8188, 0x0102, "PR_EMS_AB_CONTROL_MSG_FOLDER_ID",				"" },
	{ 0x8189, 0x001e, "PR_EMS_AB_USENET_SITE_NAME",					"" },
	{ 0x818a, 0x0102, "PR_EMS_AB_CONTROL_MSG_RULES",				"" },
	{ 0x818b, 0x001e, "PR_EMS_AB_AVAILABLE_DISTRIBUTIONS",				"" },
	{ 0x818d, 0x0102, "PR_EMS_AB_OUTBOUND_HOST",					"" },
	{ 0x818e, 0x101e, "PR_EMS_AB_INBOUND_HOST",					"" },
	{ 0x818f, 0x0003, "PR_EMS_AB_OUTGOING_MSG_SIZE_LIMIT",				"" },
	{ 0x8190, 0x0003, "PR_EMS_AB_INCOMING_MSG_SIZE_LIMIT",				"" },
	{ 0x8191, 0x000b, "PR_EMS_AB_SEND_TNEF",					"" },
	{ 0x8192, 0x0102, "PR_EMS_AB_AUTHORIZED_PASSWORD_CONFIRM",			"" },
	{ 0x8193, 0x001e, "PR_EMS_AB_INBOUND_NEWSFEED",					"" },
	{ 0x8194, 0x0003, "PR_EMS_AB_NEWSFEED_TYPE",					"" },
	{ 0x8195, 0x001e, "PR_EMS_AB_OUTBOUND_NEWSFEED",				"" },
	{ 0x8196, 0x0102, "PR_EMS_AB_NEWSGROUP_LIST",					"" },
	{ 0x8197, 0x101e, "PR_EMS_AB_NNTP_DISTRIBUTIONS",				"" },
	{ 0x8198, 0x001e, "PR_EMS_AB_NEWSGROUP",					"" },
	{ 0x8199, 0x001e, "PR_EMS_AB_MODERATOR",					"" },
	{ 0x819a, 0x001e, "PR_EMS_AB_AUTHENTICATION_TO_USE",				"" },
	{ 0x819b, 0x000b, "PR_EMS_AB_HTTP_PUB_GAL",					"" },
	{ 0x819c, 0x0003, "PR_EMS_AB_HTTP_PUB_GAL_LIMIT",				"" },
	{ 0x819e, 0x1102, "PR_EMS_AB_HTTP_PUB_PF",					"" },
	{ 0x81a1, 0x001e, "PR_EMS_AB_X500_RDN",						"" },
	{ 0x81a2, 0x001e, "PR_EMS_AB_X500_NC",						"" },
	{ 0x81a3, 0x101e, "PR_EMS_AB_REFERRAL_LIST",					"" },
	{ 0x81a4, 0x000b, "PR_EMS_AB_NNTP_DISTRIBUTIONS_FLAG",				"" },
	{ 0x81a5, 0x000d, "PR_EMS_AB_ASSOC_PROTOCOL_CFG_NNTP_O",			"" },
	{ 0x81a5, 0x001e, "PR_EMS_AB_ASSOC_PROTOCOL_CFG_NNTP",				"" },
	{ 0x81a6, 0x000d, "PR_EMS_AB_NNTP_NEWSFEEDS_O",					"" },
	{ 0x81a6, 0x101e, "PR_EMS_AB_NNTP_NEWSFEEDS",					"" },
	{ 0x81a8, 0x000b, "PR_EMS_AB_ENABLED_PROTOCOL_CFG",				"" },
	{ 0x81a9, 0x101e, "PR_EMS_AB_HTTP_PUB_AB_ATTRIBUTES",				"" },
	{ 0x81ab, 0x101e, "PR_EMS_AB_HTTP_SERVERS",					"" },
	{ 0x81ac, 0x000b, "PR_EMS_AB_MODERATED",					"" },
	{ 0x81ad, 0x001e, "PR_EMS_AB_RAS_ACCOUNT",					"" },
	{ 0x81ae, 0x0102, "PR_EMS_AB_RAS_PASSWORD",					"" },
	{ 0x81af, 0x0102, "PR_EMS_AB_INCOMING_PASSWORD",				"" },
	{ 0x81b0, 0x000b, "PR_EMS_AB_OUTBOUND_HOST_TYPE",				"" },
	{ 0x81b1, 0x000b, "PR_EMS_AB_PROXY_GENERATION_ENABLED",				"" },
	{ 0x81b2, 0x0102, "PR_EMS_AB_ROOT_NEWSGROUPS_FOLDER_ID",			"" },
	{ 0x81b3, 0x000b, "PR_EMS_AB_CONNECTION_TYPE",					"" },
	{ 0x81b4, 0x0003, "PR_EMS_AB_CONNECTION_LIST_FILTER_TYPE",			"" },
	{ 0x81b5, 0x0003, "PR_EMS_AB_PORT_NUMBER",					"" },
	{ 0x81b6, 0x101e, "PR_EMS_AB_PROTOCOL_SETTINGS",				"" },
	{ 0x81b7, 0x001e, "PR_EMS_AB_GROUP_BY_ATTR_1",					"" },
	{ 0x81b8, 0x001e, "PR_EMS_AB_GROUP_BY_ATTR_2",					"" },
	{ 0x81b9, 0x001e, "PR_EMS_AB_GROUP_BY_ATTR_3",					"" },
	{ 0x81ba, 0x001e, "PR_EMS_AB_GROUP_BY_ATTR_4",					"" },
	{ 0x81be, 0x001e, "PR_EMS_AB_VIEW_SITE",					"" },
	{ 0x81bf, 0x001e, "PR_EMS_AB_VIEW_CONTAINER_1",					"" },
	{ 0x81c0, 0x001e, "PR_EMS_AB_VIEW_CONTAINER_2",					"" },
	{ 0x81c1, 0x001e, "PR_EMS_AB_VIEW_CONTAINER_3",					"" },
	{ 0x81c2, 0x0040, "PR_EMS_AB_PROMO_EXPIRATION",					"" },
	{ 0x81c3, 0x101e, "PR_EMS_AB_DISABLED_GATEWAY_PROXY",				"" },
	{ 0x81c4, 0x0102, "PR_EMS_AB_COMPROMISED_KEY_LIST",				"" },
	{ 0x81c5, 0x000d, "PR_EMS_AB_INSADMIN_O",					"" },
	{ 0x81c5, 0x001e, "PR_EMS_AB_INSADMIN",						"" },
	{ 0x81c6, 0x000b, "PR_EMS_AB_OVERRIDE_NNTP_CONTENT_FORMAT",			"" },
	{ 0x81c7, 0x000d, "PR_EMS_AB_OBJ_VIEW_CONTAINERS_O",				"" },
	{ 0x81c7, 0x101e, "PR_EMS_AB_OBJ_VIEW_CONTAINERS",				"" },

	{ 0x8c18, 0x0003, "PR_EMS_AB_VIEW_FLAGS",					"" },
	{ 0x8c19, 0x001e, "PR_EMS_AB_GROUP_BY_ATTR_VALUE_STR",				"" },
	{ 0x8c1a, 0x000d, "PR_EMS_AB_GROUP_BY_ATTR_VALUE_DN_O",				"" },
	{ 0x8c1a, 0x001e, "PR_EMS_AB_GROUP_BY_ATTR_VALUE_DN",				"" },
	{ 0x8c1b, 0x1102, "PR_EMS_AB_VIEW_DEFINITION",					"" },
	{ 0x8c1c, 0x0102, "PR_EMS_AB_MIME_TYPES",					"" },
	{ 0x8c1d, 0x0003, "PR_EMS_AB_LDAP_SEARCH_CFG",					"" },
	{ 0x8c1e, 0x000d, "PR_EMS_AB_INBOUND_DN_O",					"" },
	{ 0x8c1e, 0x001e, "PR_EMS_AB_INBOUND_DN",					"" },
	{ 0x8c1f, 0x000b, "PR_EMS_AB_INBOUND_NEWSFEED_TYPE",				"" },
	{ 0x8c20, 0x000b, "PR_EMS_AB_INBOUND_ACCEPT_ALL",				"" },
	{ 0x8c21, 0x000b, "PR_EMS_AB_ENABLED",						"" },
	{ 0x8c22, 0x000b, "PR_EMS_AB_PRESERVE_INTERNET_CONTENT",			"" },
	{ 0x8c23, 0x000b, "PR_EMS_AB_DISABLE_DEFERRED_COMMIT",				"" },
	{ 0x8c24, 0x000b, "PR_EMS_AB_CLIENT_ACCESS_ENABLED",				"" },
	{ 0x8c25, 0x000b, "PR_EMS_AB_REQUIRE_SSL",					"" },
	{ 0x8c26, 0x001e, "PR_EMS_AB_ANONYMOUS_ACCOUNT",				"" },
	{ 0x8c27, 0x0102, "PR_EMS_AB_CERTIFICATE_CHAIN_V3",				"" },
	{ 0x8c28, 0x0102, "PR_EMS_AB_CERTIFICATE_REVOCATION_LIST_V3",			"" },
	{ 0x8c29, 0x0102, "PR_EMS_AB_CERTIFICATE_REVOCATION_LIST_V1",			"" },
	{ 0x8c30, 0x1102, "PR_EMS_AB_CROSS_CERTIFICATE_CRL",				"" },
	{ 0x8c31, 0x000b, "PR_EMS_AB_SEND_EMAIL_MESSAGE",				"" },
	{ 0x8c32, 0x000b, "PR_EMS_AB_ENABLE_COMPATIBILITY",				"" },
	{ 0x8c33, 0x101e, "PR_EMS_AB_SMIME_ALG_LIST_NA",				"" },
	{ 0x8c34, 0x101e, "PR_EMS_AB_SMIME_ALG_LIST_OTHER",				"" },
	{ 0x8c35, 0x001e, "PR_EMS_AB_SMIME_ALG_SELECTED_NA",				"" },
	{ 0x8c36, 0x001e, "PR_EMS_AB_SMIME_ALG_SELECTED_OTHER",				"" },
	{ 0x8c37, 0x000b, "PR_EMS_AB_DEFAULT_MESSAGE_FORMAT",				"" },
	{ 0x8c38, 0x001e, "PR_EMS_AB_TYPE",						"" },
	{ 0x8c3a, 0x0003, "PR_EMS_AB_DO_OAB_VERSION",					"" },
	{ 0x8c3b, 0x0102, "PR_EMS_AB_VOICE_MAIL_SYSTEM_GUID",				"" },
	{ 0x8c3c, 0x001e, "PR_EMS_AB_VOICE_MAIL_USER_ID",				"" },
	{ 0x8c3d, 0x001e, "PR_EMS_AB_VOICE_MAIL_PASSWORD",				"" },
	{ 0x8c3e, 0x0102, "PR_EMS_AB_VOICE_MAIL_RECORDED_NAME",				"" },
	{ 0x8c3f, 0x101e, "PR_EMS_AB_VOICE_MAIL_GREETINGS",				"" },
	{ 0x8c40, 0x1102, "PR_EMS_AB_VOICE_MAIL_FLAGS",					"" },
	{ 0x8c41, 0x0003, "PR_EMS_AB_VOICE_MAIL_VOLUME",				"" },
	{ 0x8c42, 0x0003, "PR_EMS_AB_VOICE_MAIL_SPEED",					"" },
	{ 0x8c43, 0x1003, "PR_EMS_AB_VOICE_MAIL_RECORDING_LENGTH",			"" },
	{ 0x8c44, 0x001e, "PR_EMS_AB_DISPLAY_NAME_SUFFIX",				"" },
	{ 0x8c45, 0x1102, "PR_EMS_AB_ATTRIBUTE_CERTIFICATE",				"" },
	{ 0x8c46, 0x1102, "PR_EMS_AB_DELTA_REVOCATION_LIST",				"" },
	{ 0x8c47, 0x1102, "PR_EMS_AB_SECURITY_POLICY",					"" },
	{ 0x8c48, 0x000b, "PR_EMS_AB_SUPPORT_SMIME_SIGNATURES",				"" },
	{ 0x8c49, 0x000b, "PR_EMS_AB_DELEGATE_USER",					"" },
	{ 0x8c50, 0x000b, "PR_EMS_AB_LIST_PUBLIC_FOLDERS",				"" },
	{ 0x8c51, 0x001e, "PR_EMS_AB_LABELEDURI",					"" },
	{ 0x8c52, 0x000b, "PR_EMS_AB_RETURN_EXACT_MSG_SIZE",				"" },
	{ 0x8c53, 0x001e, "PR_EMS_AB_GENERATION_QUALIFIER",				"" },
	{ 0x8c54, 0x001e, "PR_EMS_AB_HOUSE_IDENTIFIER",					"" },
	{ 0x8c55, 0x0102, "PR_EMS_AB_SUPPORTED_ALGORITHMS",				"" },
	{ 0x8c56, 0x001e, "PR_EMS_AB_DMD_NAME",						"" },
	{ 0x8c57, 0x001e, "PR_EMS_AB_EXTENSION_ATTRIBUTE_11",				"" },
	{ 0x8c58, 0x001e, "PR_EMS_AB_EXTENSION_ATTRIBUTE_12",				"" },
	{ 0x8c59, 0x001e, "PR_EMS_AB_EXTENSION_ATTRIBUTE_13",				"" },
	{ 0x8c60, 0x001e, "PR_EMS_AB_EXTENSION_ATTRIBUTE_14",				"" },
	{ 0x8c61, 0x001e, "PR_EMS_AB_EXTENSION_ATTRIBUTE_15",				"" },
	{ 0x8c62, 0x0003, "PR_EMS_AB_REPLICATED_OBJECT_VERSION",			"" },
	{ 0x8c63, 0x001e, "PR_EMS_AB_MAIL_DROP",					"" },
	{ 0x8c64, 0x001e, "PR_EMS_AB_FORWARDING_ADDRESS",				"" },
	{ 0x8c65, 0x0102, "PR_EMS_AB_FORM_DATA",					"" },
	{ 0x8c66, 0x001e, "PR_EMS_AB_OWA_SERVER",					"" },
	{ 0x8c67, 0x001e, "PR_EMS_AB_EMPLOYEE_NUMBER",					"" },
	{ 0x8c68, 0x001e, "PR_EMS_AB_TELEPHONE_PERSONAL_PAGER",				"" },
	{ 0x8c69, 0x001e, "PR_EMS_AB_EMPLOYEE_TYPE",					"" },
	{ 0x8c6a, 0x1102, "PR_EMS_AB_TAGGED_X509_CERT",					"" },
	{ 0x8c6b, 0x001e, "PR_EMS_AB_PERSONAL_TITLE",					"" },
	{ 0x8c6c, 0x001e, "PR_EMS_AB_LANGUAGE_ISO639",					"" },
	{ 0x8c6d, 0x001e, "PR_EMS_AB_OBJECT_GUID",					"" },
	{ 0x8c8e, 0x001e, "PR_EMS_AB_PHONETIC_GIVEN_NAME",				"" },
	{ 0x8c8f, 0x001e, "PR_EMS_AB_PHONETIC_SURNAME",					"" },
	{ 0x8c90, 0x001e, "PR_EMS_AB_PHONETIC_DEPARTMENT_NAME",				"" },
	{ 0x8c91, 0x001e, "PR_EMS_AB_PHONETIC_COMPANY_NAME",				"" },
	{ 0x8c92, 0x001e, "PR_EMS_AB_PHONETIC_DISPLAY_NAME",				"" },
	{ 0x8c96, 0x001e, "PR_EMS_AB_ROOM_CONTAINERS",					"" },

	{ 0xf000, 0x000d, "PR_EMS_AB_OTHER_RECIPS",					"" },

	{ 0xfff8, 0x101e, "PR_EMS_AB_CHILD_RDNS",					"" },
	{ 0xfff9, 0x001e, "PR_EMS_AB_HIERARCHY_PATH",					"" },
	{ 0xfffa, 0x0102, "PR_EMS_AB_OBJECT_OID",					"" },
	{ 0xfffb, 0x000b, "PR_EMS_AB_IS_MASTER",					"" },
	{ 0xfffc, 0x0102, "PR_EMS_AB_PARENT_ENTRYID",					"" },
	{ 0xfffd, 0x0003, "PR_EMS_AB_CONTAINERID",					"" },
	{ 0xfffe, 0x001e, "PR_EMS_AB_SERVER",						"" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The calendar long property types
 * Class identifier: 6ed8da90-450b-101b-98da-00aa003f1305 (PSETID_Meeting)
 */
libfmapi_property_type_t libfmapi_calendar_long_properties[ ] = {
	{ 0x00000001, 0x0040, "LID_ATTENDEE_CRITICAL_CHANGE",				"Attendee critical change" },
	{ 0x00000002, 0x001e, "LID_WHERE",						"Location" },
	{ 0x00000003, 0x0102, "LID_GLOBAL_OBJID",					"Global object identifier" },
	{ 0x00000004, 0x000b, "LID_IS_SILENT",						"Is silent" },
	{ 0x00000005, 0x000b, "PidLidIsRecurring",					"Is recurring" },
	{ 0x00000006, 0x001e, "LID_REQUIRED_ATTENDEES",					"Required attendees" },
	{ 0x00000007, 0x001e, "LID_OPTIONAL_ATTENDEES",					"Optional attendees" },
	{ 0x00000008, 0x001e, "LID_RESOURCE_ATTENDEES",					"Resource attendees" },
	{ 0x00000009, 0x000b, "LID_DELEGATE_MAIL",					"Delegate mail" },
	{ 0x0000000a, 0x000b, "LID_IS_EXCEPTION",					"Is exception" },
	{ 0x0000000b, 0x000b, "LID_SINGLE_INVITE",					"Single invite" },
	{ 0x0000000c, 0x0003, "LID_TIME_ZONE",						"Time zone" },
	{ 0x00000011, 0x0002, "LID_DAY_INTERVAL",					"Day interval" },
	{ 0x00000012, 0x0002, "LID_WEEK_INTERVAL",					"Week interval" },
	{ 0x00000013, 0x0002, "LID_MONTH_INTERVAL",					"Month interval" },
	{ 0x00000014, 0x0002, "LID_YEAR_INTERVAL",					"Year interval" },
	{ 0x0000001a, 0x0040, "LID_OWNER_CRITICAL_CHANGE",				"Owner critical change" },
	{ 0x0000001c, 0x0003, "LID_CALENDAR_TYPE",					"Calendar type" },
	{ 0x0000001d, 0x001e, "LID_ALL_ATTENDEES_LIST",					"Resource attendees" },
	{ 0x00000023, 0x0102, "PidLidCleanGlobalObjId",					"Clean global object identifier" },
	{ 0x00000024, 0x001e, "PidLidApptMessageClass",					"Appointment message class" },
	{ 0x00000026, 0x0003, "PidLidMeetingType",					"Meeting type" },
	{ 0x00000028, 0x001e, "PidLidOldLocation",					"Location before update" },
	{ 0x00000029, 0x0040, "PidLidOldWhenStartWhole",				"Start time before update" },
	{ 0x0000002a, 0x0040, "PidLidOldWhenEndWhole",					"End time before update" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The address long property types
 * Class identifier: 00062004-0000-0000-c000-000000000046 (PSETID_Address)
 */
libfmapi_property_type_t libfmapi_address_long_properties[ ] = {
	{ 0x00008002, 0x001e, "PidLidYomiCompanyName",					"" },
	{ 0x00008005, 0x001e, "PidLidFileUnder",					"File under" },
	{ 0x00008006, 0x0003, "PidLidFileUnderID",					"File under identifier" },
	{ 0x00008007, 0x1003, "PidLidContactItemData",					"" },
	{ 0x0000800e, 0x001f, "",							"" },
	{ 0x00008010, 0x001e, "PidLidDepartment",					"Department" },
	{ 0x00008015, 0x000b, "PidLidHasPicture",					"Has picture" },
	{ 0x0000801a, 0x001e, "PidLidHomeAddress",					"Home address" },
	{ 0x0000801b, 0x001e, "PidLidWorkAddress",					"Business address" },
	{ 0x0000801c, 0x001e, "PidLidOtherAddress",					"Other address" },
	{ 0x00008022, 0x001e, "PidLidPostalAddressId",					"Selected mailing address" },
	{ 0x00008023, 0x0003, "PidLidContactCharacterSet",				"" },
	{ 0x00008025, 0x000b, "PidLidAutoLog",						"Journal" },
	{ 0x00008026, 0x1003, "PidLidFileUnderList",					"" },
	{ 0x00008027, 0x1003, "PidLidEmailList",					"" },
	{ 0x00008028, 0x1003, "PidLidAddressBookProviderEmailList",			"" },
	{ 0x00008029, 0x0003, "PidLidAddressBookProviderArrayType",			"Address book provider types" },
	{ 0x0000802b, 0x001e, "PidLidHtml",						"Webpage" },
	{ 0x0000802c, 0x001e, "PidLidYomiFirstName",					"" },
	{ 0x0000802d, 0x001e, "PidLidYomiLastName",					"" },
	{ 0x00008040, 0x0102, "PidLidBusinessCardDisplayDefinition",			"" },
	{ 0x00008041, 0x0102, "PidLidBusinessCardCardPicture",				"" },
	{ 0x00008045, 0x001e, "PidLidWorkAddressStreet",				"Business address city" },
	{ 0x00008046, 0x001e, "PidLidWorkAddressCity",					"Business address street" },
	{ 0x00008047, 0x001e, "PidLidWorkAddressState",					"Business address state" },
	{ 0x00008048, 0x001e, "PidLidWorkAddressPostalCode",				"Business address postal code" },
	{ 0x00008049, 0x001e, "PidLidWorkAddressCountry",				"Business address country" },
	{ 0x0000804a, 0x001e, "PidLidWorkAddressPostOfficeBox",				"" },
	{ 0x0000804c, 0x0003, "PidLidDistributionListChecksum",				"Distribution list checksum" },
	{ 0x0000804d, 0x0102, "PidLidBirthdayEventEntryId",				"" },
	{ 0x0000804e, 0x0102, "PidLidAnniversaryEventEntryId",				"" },
	{ 0x0000804f, 0x001e, "PidLidContactUserField1",				"" },
	{ 0x00008050, 0x001e, "PidLidContactUserField2",				"" },
	{ 0x00008051, 0x001e, "PidLidContactUserField3",				"" },
	{ 0x00008052, 0x001e, "PidLidContactUserField4",				"" },
	{ 0x00008053, 0x001e, "PidLidDistributionListName",				"Distribution list name" },
	{ 0x00008054, 0x1102, "PidLidDistributionListOneOffMembers",			"Distribution list member one-off entry identifiers" },
	{ 0x00008055, 0x1102, "PidLidDistributionListMembers",				"Distribution list member entry identifiers" },
	{ 0x00008062, 0x001e, "PidLidInstantMessagingAddress",				"IM Address" },
	{ 0x00008080, 0x001e, "PidLidEmail1DisplayName",				"E-mail1 Display Name" },
	{ 0x00008081, 0x0102, "PidLidEmail1EntryId",					"E-mail1 entry identifier" },
	{ 0x00008082, 0x001e, "PidLidEmail1AddressType",				"E-mail1 Address Type" },
	{ 0x00008083, 0x001e, "PidLidEmail1EmailAddress",				"E-mail1 Address" },
	{ 0x00008084, 0x001e, "PidLidEmail1OriginalDisplayName",			"E-mail1 Display Name" },
	{ 0x00008085, 0x0102, "PidLidEmail1OriginalEntryId",				"E-mail1 original entry identifier" },
	{ 0x00008087, 0x001e, "PidLidEmail1EmailType",					"E-mail1 type" },
	{ 0x00008090, 0x001e, "PidLidEmail2DisplayName",				"E-mail2 display name" },
	{ 0x00008091, 0x0102, "PidLidEmail2EntryId",					"E-mail2 entry identifier" },
	{ 0x00008092, 0x001e, "PidLidEmail2AddressType",				"E-mail2 address type" },
	{ 0x00008093, 0x001e, "PidLidEmail2EmailAddress",				"E-mail2 e-mail address" },
	{ 0x00008094, 0x001e, "PidLidEmail2OriginalDisplayName",			"E-mail2 original display name" },
	{ 0x00008095, 0x0102, "PidLidEmail2OriginalEntryId",				"E-mail2 original entry identifier" },
	{ 0x000080a0, 0x001e, "PidLidEmail3DisplayName",				"E-mail3 display name" },
	{ 0x000080a1, 0x0102, "PidLidEmail3EntryId",					"E-mail3 entry identifier" },
	{ 0x000080a2, 0x001e, "PidLidEmail3AddressType",				"E-mail3 address type" },
	{ 0x000080a3, 0x001e, "PidLidEmail3EmailAddress",				"E-mail3 e-mail address" },
	{ 0x000080a4, 0x001e, "PidLidEmail3OriginalDisplayName",			"E-mail3 original display name" },
	{ 0x000080a5, 0x0102, "PidLidEmail3OriginalEntryId",				"E-mail3 original entry identifier" },
	{ 0x000080b2, 0x001e, "PidLidFax1AddressType",					"Fax1 Address Type" },
	{ 0x000080b3, 0x001e, "PidLidFax1EmailAddress",					"Fax1 Email Address" },
	{ 0x000080b4, 0x001e, "PidLidFax1OriginalDisplayName",				"Fax1 original display name" },
	{ 0x000080b5, 0x0102, "PidLidFax1OriginalEntryId",				"Fax1 original entry identifier" },
	{ 0x000080c2, 0x001e, "PidLidFax2AddressType",					"Fax2 Address Type" },
	{ 0x000080c3, 0x001e, "PidLidFax2EmailAddress",					"Fax2 Email Address" },
	{ 0x000080c4, 0x001e, "PidLidFax2OriginalDisplayName",				"Fax2 original display name" },
	{ 0x000080c5, 0x0102, "PidLidFax2OriginalEntryId",				"Fax2 original entry identifier" },
	{ 0x000080d2, 0x001e, "PidLidFax3AddressType",					"Fax3 Address Type" },
	{ 0x000080d3, 0x001e, "PidLidFax3EmailAddress",					"Fax3 Email Address" },
	{ 0x000080d4, 0x001e, "PidLidFax3OriginalDisplayName",				"Fax3 original display name" },
	{ 0x000080d5, 0x0102, "PidLidFax3OriginalEntryId",				"Fax3 original entry identifier" },
	{ 0x000080d8, 0x001e, "PidLidFreeBusyLocation",					"" },
	{ 0x000080da, 0x001e, "PidLidHomeAddressCountryCode",				"Home address country code" },
	{ 0x000080db, 0x001e, "PidLidWorkAddressCountryCode",				"Work address country code" },
	{ 0x000080dc, 0x001e, "PidLidOtherAddressCountryCode",				"Other address country code" },
	{ 0x000080dd, 0x001e, "PidLidAddressCountryCode",				"Mailing address country code" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The task long property types
 * Class identifier: 00062003-0000-0000-c000-000000000046 (PSETID_Task)
 */
libfmapi_property_type_t libfmapi_task_long_properties[ ] = {
	{ 0x00008101, 0x0003, "PidLidTaskStatus",					"Status" },
	{ 0x00008102, 0x0005, "PidLidPercentComplete",					"Percent complete" },
	{ 0x00008103, 0x000b, "PidLidTeamTask",						"Is team task" },
	{ 0x00008104, 0x0040, "PidLidTaskStartDate",					"Start date" },
	{ 0x00008105, 0x0040, "PidLidTaskDueDate",					"Due date" },
	{ 0x00008107, 0x000b, "PidLidTaskResetReminder",				"" },
	{ 0x00008108, 0x000b, "PidLidTaskAccepted",					"" },
	{ 0x00008109, 0x000b, "PidLidTaskDeadOccurrence",				"" },
	{ 0x0000810f, 0x0040, "PidLidTaskDateCompleted",				"Date completed" },
	{ 0x00008110, 0x0003, "PidLidTaskActualEffort",					"Actual effort in minutes" },
	{ 0x00008111, 0x0003, "PidLidTaskEstimatedEffort",				"Total effort in minutes" },
	{ 0x00008112, 0x0003, "PidLidTaskVersion",					"" },
	{ 0x00008113, 0x0003, "PidLidTaskState",					"" },
	{ 0x00008115, 0x0040, "PidLidTaskLastUpdate",					"" },
	{ 0x00008116, 0x0102, "PidLidTaskRecurrence",					"" },
	{ 0x00008117, 0x0102, "PidLidTaskAssigners",					"" },
	{ 0x00008119, 0x000b, "PidLidTaskStatusOnComplete",				"" },
	{ 0x0000811a, 0x0003, "PidLidTaskHistory",					"" },
	{ 0x0000811b, 0x000b, "PidLidTaskUpdates",					"" },
	{ 0x0000811c, 0x000b, "PidLidTaskComplete",					"Is complete" },
	{ 0x0000811e, 0x000b, "PidLidTaskFCreator",					"" },
	{ 0x0000811f, 0x001e, "PidLidTaskOwner",					"Owner" },
	{ 0x00008120, 0x0003, "PidLidTaskMultipleRecipients",				"" },
	{ 0x00008121, 0x001e, "PidLidTaskAssigner",					"Delegator" },
	{ 0x00008122, 0x001e, "PidLidTaskLastUser",					"" },
	{ 0x00008123, 0x0003, "PidLidTaskOrdinal",					"Ordinal" },
	{ 0x00008124, 0x000b, "PidLidTaskNoCompute",					"" },
	{ 0x00008125, 0x001e, "PidLidTaskLastDelegate",					"" },
	{ 0x00008126, 0x000b, "PidLidTaskFRecurring",					"Is recurring" },
	{ 0x00008127, 0x001e, "PidLidTaskRole",						"Role" },
	{ 0x00008129, 0x0003, "PidLidTaskOwnership",					"Ownership" },
	{ 0x0000812a, 0x0003, "PidLidAcceptanceState",					"Delegation State" },
	{ 0x0000812c, 0x000b, "PidLidTaskFFixOffline",					"" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The appointment long property types
 * Class identifier: 00062002-0000-0000-c000-000000000046 (PSETID_Appointment)
 */
libfmapi_property_type_t libfmapi_appointment_long_properties[ ] = {
	{ 0x00008200, 0x000b, "PidLidSendMeetingAsIcal",				"Send as ICAL" },
	{ 0x00008201, 0x0003, "PidLidAppointmentSequence",				"Appointment sequence" },
	{ 0x00008202, 0x0040, "PidLidAppointmentSequenceTime",				"Appointment sequence last modification date and time" },
	{ 0x00008203, 0x0003, "PidLidAppointmentLastSequence",				"Appointment last sequence number" },
	{ 0x00008204, 0x0003, "PidLidChangeHighlight",					"" },
	{ 0x00008205, 0x0003, "PidLidBusyStatus",					"Busy status" },
	{ 0x00008206, 0x000b, "PidLidFExceptionalBody",					"" },
	{ 0x00008207, 0x0003, "PidLidAppointmentAuxiliaryFlags",			"" },
	{ 0x00008208, 0x001e, "PidLidLocation",						"Location" },
	{ 0x00008209, 0x001e, "PidLidMeetingWorkspaceUrl",				"" },
	{ 0x0000820a, 0x000b, "PidLidForwardInstance",					"" },
	{ 0x0000820c, 0x1102, "PidLidLinkedTaskItems",					"" },
	{ 0x0000820d, 0x0040, "PidLidAppointmentStartWhole",				"Start time" },
	{ 0x0000820e, 0x0040, "PidLidAppointmentEndWhole",				"End time" },
	{ 0x00008213, 0x0003, "PidLidAppointmentDuration",				"Duration in minutes" },
	{ 0x00008214, 0x0003, "PidLidAppointmentColor",					"Color" },
	{ 0x00008215, 0x000b, "PidLidAppointmentSubType",				"Sub type" },
	{ 0x00008216, 0x0102, "PidLidAppointmentRecur",					"" },
	{ 0x00008217, 0x0003, "PidLidAppointmentStateFlags",				"Meeting status" },
	{ 0x00008218, 0x0003, "PidLidResponseStatus",					"Response status" },
	{ 0x00008220, 0x0040, "PidLidAppointmentReplyTime",				"" },
	{ 0x00008223, 0x000b, "PidLidRecurring",					"Is recurrent" },
	{ 0x00008224, 0x0003, "PidLidIntendedBusyStatus",				"" },
	{ 0x00008228, 0x0040, "PidLidExceptionReplaceTime",				"Recurrence Base" },
	{ 0x00008229, 0x000b, "PidLidFInvited",						"" },
	{ 0x0000822b, 0x000b, "PidLidFExceptionalAttendees",				"" },
	{ 0x00008230, 0x001e, "PidLidAppointmentReplyName",				"" },
	{ 0x00008231, 0x0003, "PidLidRecurrenceType",					"Recurrence Type" },
	{ 0x00008232, 0x001e, "PidLidRecurrencePattern",				"Recurrence Pattern" },
	{ 0x00008233, 0x0102, "PidLidTimeZoneStruct",					"" },
	{ 0x00008234, 0x001e, "PidLidTimeZoneDescription",				"Time zone" },
	{ 0x00008235, 0x0040, "PidLidClipStart",					"First effective time" },
	{ 0x00008236, 0x0040, "PidLidClipEnd",						"Last effective time" },
	{ 0x00008237, 0x0102, "PidLidOriginalStoreEntryId",				"" },
	{ 0x00008238, 0x001e, "PidLidAllAttendeesString",				"All Attendees" },
	{ 0x0000823a, 0x000b, "PidLidAutoFillLocation",					"" },
	{ 0x0000823b, 0x001e, "PidLidToAttendeesString",				"To Attendees" },
	{ 0x0000823c, 0x001e, "PidLidCcAttendeesString",				"CC Attendees" },
	{ 0x0000823d, 0x0003, "PidLidAppointmentUnsendableRecipients",			"" },
	{ 0x00008240, 0x000b, "PidLidConferencingCheck",				"Is an online meeting" },
	{ 0x00008241, 0x0003, "PidLidConferencingType",					"Net meeting type" },
	{ 0x00008242, 0x001e, "PidLidDirectory",					"Net meeting server" },
	{ 0x00008243, 0x001e, "PidLidOrganizerAlias",					"Net meeting organizer alias" },
	{ 0x00008244, 0x000b, "PidLidAutoStartCheck",					"Net meeting auto start" },
	{ 0x00008245, 0x0003, "PidLidAutoStartWhen",					"" },
	{ 0x00008246, 0x000b, "PidLidAllowExternalCheck",				"Conference server allow external" },
	{ 0x00008247, 0x001e, "PidLidCollaborateDoc",					"Net meeting document path name" },
	{ 0x00008248, 0x001e, "PidLidNetShowUrl",					"Net show URL" },
	{ 0x00008249, 0x001e, "PidLidOnlinePassword",					"Conference server password" },
	{ 0x00008250, 0x0040, "PidLidAppointmentProposedStartWhole",			"" },
	{ 0x00008251, 0x0040, "PidLidAppointmentProposedEndWhole",			"" },
	{ 0x00008256, 0x0003, "PidLidAppointmentProposedDuration",			"" },
	{ 0x00008257, 0x000b, "PidLidAppointmentCounterProposal",			"Appointment counter proposal" },
	{ 0x00008259, 0x0003, "PidLidAppointmentProposalNumber",			"" },
	{ 0x0000825a, 0x000b, "PidLidAppointmentNotAllowPropose",			"" },
	{ 0x0000825e, 0x0102, "PidLidAppointmentTimeZoneDefinitionStartDisplay",	"Appointment start time time zone" },
	{ 0x0000825f, 0x0102, "PidLidAppointmentTimeZoneDefinitionEndDisplay",		"Appointment end time time zone" },
	{ 0x00008260, 0x0102, "PidLidAppointmentTimeZoneDefinitionRecur",		"" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The common long property types
 * Class identifier: 0062008-0000-0000-c000-000000000046 (PSETID_Common)
 */
libfmapi_property_type_t libfmapi_common_long_properties[ ] = {
	{ 0x00008501, 0x0003, "PidLidReminderDelta",					"Reminder minutes before start" },
	{ 0x00008502, 0x0040, "PidLidReminderTime",					"Reminder time" },
	{ 0x00008503, 0x000b, "PidLidReminderSet",					"Is reminder" },
	{ 0x00008506, 0x000b, "PidLidPrivate",						"Is private" },
	{ 0x0000850e, 0x000b, "PidLidAgingDontAgeMe",					"No aging" },
	{ 0x00008510, 0x0003, "PidLidSideEffects",					"Side effects" },
	{ 0x00008514, 0x000b, "PidLidSmartNoAttach",					"" },
	{ 0x00008516, 0x0040, "PidLidCommonStart",					"Common start time" },
	{ 0x00008517, 0x0040, "PidLidCommonEnd",					"Common end time" },
	{ 0x00008518, 0x0003, "PidLidTaskMode",						"Task mode" },
	{ 0x00008519, 0x0102, "PidLidTaskGlobalId",					"" },
	{ 0x0000851a, 0x0003, "PidLidAutoProcessState",					"" },
	{ 0x0000851c, 0x000b, "PidLidReminderOverride",					"" },
	{ 0x0000851d, 0x0003, "PidLidReminderType",					"" },
	{ 0x0000851e, 0x000b, "PidLidReminderPlaySound",				"" },
	{ 0x0000851f, 0x001e, "PidLidReminderFileParameter",				"Reminder sound filename" },
	{ 0x00008520, 0x0102, "PidLidVerbStream",					"" },
	{ 0x00008524, 0x001e, "PidLidVerbResponse",					"" },
	{ 0x00008530, 0x001e, "PidLidFlagRequest",					"" },
	{ 0x00008534, 0x001e, "PidLidMileage",						"Mileage" },
	{ 0x00008535, 0x001e, "PidLidBillingInformation",				"Billing information" },
	{ 0x00008536, 0x001e, "PidLidNonSendtableTo",					"" },
	{ 0x00008537, 0x001e, "PidLidNonSendableCc",					"" },
	{ 0x00008538, 0x001e, "PidLidNonSendableBcc",					"" },
	{ 0x00008539, 0x101e, "PidLidCompanies",					"Companies" },
	{ 0x0000853a, 0x101e, "PidLidContacts",						"Contacts" },
	{ 0x00008543, 0x1003, "PidLidNonSendToTrackStatus",				"" },
	{ 0x00008544, 0x1003, "PidLidNonSendCcTrackStatus",				"" },
	{ 0x00008545, 0x1003, "PidLidNonSendBccTrackStatus",				"" },
	{ 0x00008552, 0x0003, "PidLidCurrentVersion",					"Outlook internal version" },
	{ 0x00008554, 0x001e, "PidLidCurrentVersionName",				"Outlook version" },
	{ 0x00008560, 0x0040, "PidLidReminderSignalTime",				"Reminder signal time" },
	{ 0x00008580, 0x001e, "PidLidInternetAccountName",				"E-mail account name" },
	{ 0x00008581, 0x001e, "PidLidInternetAccountStamp",				"E-mail account identifier" },
	{ 0x00008582, 0x000b, "PidLidUseTnef",						"Use TNEF" },
	{ 0x00008584, 0x0102, "PidLidContactLinkSearchKey",				"" },
	{ 0x00008585, 0x0102, "PidLidContactLinkEntry",					"" },
	{ 0x00008586, 0x001e, "PidLidContactLinkName",					"" },
	{ 0x0000859c, 0x0102, "PidLidSpamOriginalFolder",				"" },
	{ 0x000085a0, 0x0040, "PidLidToDoOrdinalDate",					"" },
	{ 0x000085a1, 0x001e, "PidLidToDoSubOrdinal",					"" },
	{ 0x000085a4, 0x001e, "PidLidToDoTitle",					"" },
	{ 0x000085b1, 0x001e, "PidLidInfoPathFormName",					"" },
	{ 0x000085b5, 0x000b, "PidLidClassified",					"" },
	{ 0x000085b6, 0x001e, "PidLidClassification",					"" },
	{ 0x000085b7, 0x001e, "PidLidClassificationDescription",			"" },
	{ 0x000085b8, 0x001e, "PidLidClassificationGuid",				"" },
	{ 0x000085ba, 0x000b, "PidLidClassificationKeep",				"" },
	{ 0x000085bd, 0x0102, "PidLidReferenceEntryId",					"" },
	{ 0x000085bf, 0x0040, "PidLidValidFlagStringProof",				"" },
	{ 0x000085c0, 0x0003, "PidLidFlagString",					"" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The journal long property types
 * Class identifier: 0006200a-0000-0000-c000-000000000046 (PSETID_Log)
 */
libfmapi_property_type_t libfmapi_journal_long_properties[ ] = {
	{ 0x00008700, 0x001e, "PidLidLogType",						"Type" },
	{ 0x00008706, 0x0040, "PidLidLogStart",						"Start" },
	{ 0x00008707, 0x0003, "PidLidLogDuration",					"Duration" },
	{ 0x00008708, 0x0040, "PidLidLogEnd",						"End" },
	{ 0x0000870c, 0x0003, "PidLidLogFlags",						"LogFlags" },
	{ 0x0000870e, 0x000b, "PidLidDocumentPrinted",					"DocPrinted" },
	{ 0x0000870f, 0x000b, "PidLidDocumentSaved",					"DocSaved" },
	{ 0x00008710, 0x000b, "PidLidDocumentRouted",					"DocRouted" },
	{ 0x00008711, 0x000b, "PidLidDocumentPosted",					"DocPosted" },
	{ 0x00008712, 0x001e, "PidLidLogTypeDesc",					"TypeDescription" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The RSS feed long property types
 * Class identifier: 00062041-0000-0000-c000-000000000046 (PSETID_PostRSS)
 */
libfmapi_property_type_t libfmapi_rss_feed_long_properties[ ] = {
	{ 0x00008900, 0x001e, "PidLidPostRssChannelLink",				"Channel" },
	{ 0x00008901, 0x001e, "PidLidPostRssItemLink",					"Item link" },
	{ 0x00008902, 0x0003, "PidLidPostRssItemHash",					"Item Hash" },
	{ 0x00008903, 0x001e, "PidLidPostRssItemGuid",					"Item GUID" },
	{ 0x00008904, 0x001e, "PidLidPostRssChannel",					"Channel GUID" },
	{ 0x00008905, 0x001e, "PidLidPostRssItemXml",					"Item XML" },
	{ 0x00008906, 0x001e, "PidLidPostRssSubscription",				"Subscription" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The Sharing long property types
 * Class identifier: 0062040-0000-0000-c000-000000000046 (PSETID_Sharing)
 */
libfmapi_property_type_t libfmapi_sharing_long_properties[ ] = {
	{ 0x00008a00, 0x0003, "PidLidSharingStatus",						"" },
	{ 0x00008a01, 0x0102, "PidLidSharingProviderGuid",					"" },
	{ 0x00008a02, 0x001e, "PidLidSharingProviderName",					"" },
	{ 0x00008a03, 0x001e, "PidLidSharingProviderUrl",					"" },
	{ 0x00008a04, 0x001e, "PidLidSharingRemotePath",					"" },
	{ 0x00008a05, 0x001e, "PidLidSharingRemoteName",					"" },
	{ 0x00008a06, 0x001e, "PidLidSharingRemoteUid",						"" },
	{ 0x00008a07, 0x001e, "PidLidSharingInitiatorName",					"" },
	{ 0x00008a08, 0x001e, "PidLidSharingInitiatorSmtp",					"" },
	{ 0x00008a09, 0x0102, "PidLidSharingInitiatorEntryId",					"" },
	{ 0x00008a0a, 0x0003, "PidLidSharingFlags",						"" },
	{ 0x00008a0b, 0x001e, "PidLidSharingProviderExtension",					"" },
	{ 0x00008a0c, 0x001e, "PidLidSharingRemoteUser",					"" },
	{ 0x00008a0d, 0x001e, "PidLidSharingRemotePass",					"" },
	{ 0x00008a0e, 0x001e, "PidLidSharingLocalPath",						"" },
	{ 0x00008a0f, 0x001e, "PidLidSharingLocalName",						"" },
	{ 0x00008a10, 0x001e, "PidLidSharingLocalUid",						"" },
	{ 0x00008a13, 0x0102, "PidLidSharingFilter",						"" },
	{ 0x00008a14, 0x001e, "PidLidSharingLocalType",						"" },
	{ 0x00008a15, 0x0102, "PidLidSharingFolderEntryId",					"" },
	{ 0x00008a17, 0x0003, "PidLidSharingCapabilities",					"" },
	{ 0x00008a18, 0x0003, "PidLidSharingFlavor",						"" },
	{ 0x00008a19, 0x0003, "PidLidSharingAnonymity",						"" },
	{ 0x00008a1a, 0x0003, "PidLidSharingReciprocation",					"" },
	{ 0x00008a1b, 0x0003, "PidLidSharingPermissions",					"" },
	{ 0x00008a1c, 0x0102, "PidLidSharingInstanceGuid",					"" },
	{ 0x00008a1d, 0x001e, "PidLidSharingRemoteType",					"" },
	{ 0x00008a1e, 0x001e, "PidLidSharingParticipants",					"" },
	{ 0x00008a1f, 0x0040, "PidLidSharingLastSyncTime",					"" },
	{ 0x00008a21, 0x001e, "PidLidSharingExtensionXml",					"" },
	{ 0x00008a22, 0x0040, "PidLidSharingRemoteLastModificationTime",			"" },
	{ 0x00008a23, 0x0040, "PidLidSharingLocalLastModificationTime",				"" },
	{ 0x00008a24, 0x001e, "PidLidSharingConfigurationUrl",					"" },
	{ 0x00008a25, 0x0040, "PidLidSharingStart",						"" },
	{ 0x00008a26, 0x0040, "PidLidSharingStop",						"" },
	{ 0x00008a27, 0x0003, "PidLidSharingResponseType",					"" },
	{ 0x00008a28, 0x0040, "PidLidSharingResponseTime",					"" },
	{ 0x00008a29, 0x0102, "PidLidSharingOriginalMessageEntryId",				"" },
	{ 0x00008a2a, 0x0003, "PidLidSharingSyncInterval",					"" },
	{ 0x00008a2b, 0x0003, "PidLidSharingDetail",						"" },
	{ 0x00008a2c, 0x0003, "PidLidSharingTimeToLive",					"" },
	{ 0x00008a2d, 0x0102, "PidLidSharingBindingEntryId",					"" },
	{ 0x00008a2e, 0x0102, "PidLidSharingIndexEntryId",					"" },
	{ 0x00008a2f, 0x001e, "PidLidSharingRemoteComment",					"" },
	{ 0x00008a40, 0x0040, "PidLidSharingWorkingHoursStart",					"" },
	{ 0x00008a41, 0x0040, "PidLidSharingWorkingHoursEnd",					"" },
	{ 0x00008a42, 0x0003, "PidLidSharingWorkingHoursDay",					"" },
	{ 0x00008a43, 0x0102, "PidLidSharingWorkingHoursTimeZone",				"" },
	{ 0x00008a44, 0x0040, "PidLidSharingDataRangeStart",					"" },
	{ 0x00008a45, 0x0040, "PidLidSharingDataRangeEnd",					"" },
	{ 0x00008a46, 0x0003, "PidLidSharingRangeStart",					"" },
	{ 0x00008a47, 0x0003, "PidLidSharingRangeEnd",						"" },
	{ 0x00008a48, 0x001e, "PidLidSharingRemoteStoreUid",					"" },
	{ 0x00008a49, 0x001e, "PidLidSharingLocalStoreUid",					"" },
	{ 0x00008a4b, 0x0003, "PidLidSharingRemoteByteSize",					"" },
	{ 0x00008a4c, 0x0003, "PidLidSharingRemoteCrc",						"" },
	{ 0x00008a4d, 0x001e, "PidLidSharingLocalComment",					"" },
	{ 0x00008a4e, 0x0003, "PidLidSharingRoamLog",						"" },
	{ 0x00008a4f, 0x0003, "PidLidSharingRemoteMessageCount",				"" },
	{ 0x00008a51, 0x001e, "PidLidSharingBrowseUrl",						"" },
	{ 0x00008a55, 0x0040, "PidLidSharingLastAutoSyncTime",					"" },
	{ 0x00008a56, 0x0003, "PidLidSharingTimeToLiveAuto",					"" },
	{ 0x00008a5b, 0x001e, "PidLidSharingRemoteVersion",					"" },
	{ 0x00008a5c, 0x0102, "PidLidSharingParentBindingEntryId",				"" },
	{ 0x00008a60, 0x0003, "PidLidSharingSyncFlags",						"" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The Sticky note long property types
 * Class identifier: 0006200e-0000-0000-c000-000000000046 (PSETID_Note)
 */
libfmapi_property_type_t libfmapi_sticky_note_long_properties[ ] = {
	{ 0x00008b00, 0x0003, "PidLidNoteColor",					"Color" },
	{ 0x00008b02, 0x0003, "PidLidNoteWidth",					"Width" },
	{ 0x00008b03, 0x0003, "PidLidNoteHeight",					"Height" },
	{ 0x00008b04, 0x0003, "PidLidNoteX",						"Left" },
	{ 0x00008b05, 0x0003, "PidLidNoteY",						"Top" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The Public strings long property types
 * Class identifier: 0020329-0000-0000-c000-000000000046 (PS_PUBLIC_STRINGS)
 */
libfmapi_property_type_t libfmapi_public_strings_long_properties[ ] = {
	{ 0x00002328, 0x101e, "PidLidCategories",					"Categories" },

	{ (uint32_t) -1, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The Public strings named property types
 * Class identifier: 0020329-0000-0000-c000-000000000046 (PS_PUBLIC_STRINGS)
 */
libfmapi_named_property_type_t libfmapi_public_strings_named_properties[ ] = {
	{  8, "AppName",							0x001e,	"PidNameApplicationName",		"Application name" },
	{  7, "Author",								0x001e, "PidNameAuthor",			"Author" },
	{ 10, "ByteCount",							0x0003, "PidNameByteCount",			"Byte size" },
	{  9, "Category",							0x001e, "PidNameCategory",			"Category" },
	{ 10, "CharCount",							0x0003, "PidNameCharacterCount",		"Number of characters" },
	{  9, "Comments",							0x001e, "PidNameComments",			"Comments" },
	{  8, "Company",							0x001e, "PidNameCompany",			"Company" },
	{ 12, "CreateDtmRo",							0x0040, "PidNameCreateDateTimeReadOnly",	"Read only creation time" },
	{ 11, "DRMLicense",							0x1102, "PidNameRightsManagementLicense",	"Digital rights management license" },
	{  9, "EditTime",							0x001e, "PidNameEditTime",			"" },
	{ 57, "http://schemas.microsoft.com/exchange/junkemailmovestamp",	0x0003, "PidNameJunkEmailMoveStamp",		"" },
	{ 12, "HiddenCount",							0x0003, "PidNameHiddenCount",			"" },
	{  9, "Keywords",							0x101e, "PidNameKeywords",			"Keywords" },
	{ 11, "LastAuthor",							0x001e, "PidNameLastAuthor",			"" },
	{ 12, "LastPrinted",							0x0040, "PidNameLastPrinted",			"" },
	{ 12, "LastSaveDtm",							0x0040, "PidNameLastSaveDateTime",		"" },
	{ 10, "LineCount",							0x0003, "PidNameLineCount",			"" },
	{  8, "Manager",							0x001e, "PidNameManager",			"" },
	{ 12, "MMClipCount",							0x0003, "PidNameMultimediaClipCount",		"" },
	{ 10, "NoteCount",							0x0003, "PidNameNoteCount",			"" },
	{ 15, "OMSAccountGuid",							0x001e, "PidNameOMSAccountGuid",		"" },
	{ 15, "OMSMobileModel",							0x001e, "PidNameOMSMobileModel",		"" },
	{ 16, "OMSScheduleTime",						0x0040, "PidNameOMSGScheduleTime",		"" },
	{ 15, "OMSServiceType",							0x0003, "PidNameOMSServiceType",		"" },
	{ 14, "OMSSourceType",							0x0003, "PidNameOMSSourceType",			"" },
	{ 51, "http://schemas.microsoft.com/outlook/phishingstamp",		0x0003, "PidNamePhishingStamp",			"" },
	{ 10, "PageCount",							0x0003, "PidNamePageCount",			"" },
	{  9, "ParCount",							0x0003, "PidNameParagraphCount",		"" },
	{ 11, "PresFormat",							0x001e, "PidNamePresentationFormat",		"" },
	{  9, "Security",							0x0003, "PidNameSecurity",			"" },
	{ 11, "SlideCount",							0x0003, "PidNameSlideCount",			"" },
	{  8, "Subject",							0x001e, "PidNameSubject",			"" },
	{  9, "Template",							0x001e, "PidNameTemplate",			"" },
	{  6, "Title",								0x001e, "PidNameTitle",				"" },
	{ 10, "WordCount",							0x0003, "PidNameWordCount",			"" },

	{ (size_t) -1, NULL, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The Internet headers named property types
 * Class identifier: 00020386-0000-0000-c000-000000000046 (PS_INTERNET_HEADERS)
 */
libfmapi_named_property_type_t libfmapi_internet_headers_named_properties[ ] = {
	{ 17, "Accept-Language",						0x001e, "PidNameAcceptLanguage",		"Accept language" },
	{ 13, "Content-Base",							0x001e, "PidNameBodyContentBase",		"Body content base" },
	{ 14, "Content-Class",							0x001e, "PidNameContentClass",			"Content class" },
	{ 27, "Content-Transfer-Encoding",					0x001e, "PidNameContentTransferEncoding",	"Content transfer encoding" },
	{ 14, "Content-Type",							0x001e, "PidNameContentType",			"Content type" },
	{  5, "Xref",								0x001e, "PidNameCrossReference",		"Cross reference (Xref)" },
	{ 21, "X-Sharing-Browse-Url",						0x001e, "PidNameXSharingBrowseUrl",		"Sharing browse URL" },
	{ 23, "X-Sharing-Capabilities",						0x001e, "PidNameXSharingCapabilities",		"Sharing capabilities" },
	{ 21, "X-Sharing-Config-Url",						0x001e, "PidNameXSharingConfigUrl",		"Sharing configuration URL" },
	{ 24, "X-Sharing-Extended-Caps",					0x001e, "PidNameXSharingExtendedCaps",		"" },
	{ 17, "X-Sharing-Flavor",						0x001e, "PidNameXSharingFlavor",		"" },
	{ 24, "X-Sharing-Instance-Guid",					0x001e, "PidNameXSharingInstanceGuid",		"" },
	{ 21, "X-Sharing-Local-Type",						0x001e, "PidNameXSharingLocalType",		"" },
	{ 24, "X-Sharing-Provider-Guid",					0x001e, "PidNameXSharingProviderGuid",		"" },
	{ 24, "X-Sharing-Provider-Name",					0x001e, "PidNameXSharingProviderName",		"" },
	{ 23, "X-Sharing-Provider-Url",						0x001e, "PidNameXSharingProviderUrl",		"" },
	{ 22, "X-Sharing-Remote-Name",						0x001e, "PidNameXSharingRemoteName",		"" },
	{ 22, "X-Sharing-Remote-Path",						0x001e, "PidNameXSharingRemotePath",		"" },
	{ 27, "X-Sharing-Remote-Store-Uid",					0x001e, "PidNameXSharingRemoteStoreUid",	"" },
	{ 22, "X-Sharing-Remote-Type",						0x001e, "PidNameXSharingRemoteType",		"" },
	{ 21, "X-Sharing-Remote-Uid",						0x001e, "PidNameXSharingRemoteUid",		"" },

	{ (size_t) -1, NULL, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The Attachment named property types
 * Class identifier: 96357f7f-59e1-47d0-99a7-46515c183b54 (PSETID_Attachment)
 */
libfmapi_named_property_type_t libfmapi_attachment_named_properties[ ] = {
	{ 25, "AttachmentMacContentType",					0x001e, "PidNameAttachmentMacContentType",	"Attachment content type for Apple Macintosh" },
	{ 18, "AttachmentMacInfo",						0x0102, "PidNameAttachmentMacInfo",		"Attachment information for Apple Macintosh" },

	{ (size_t) -1, NULL, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* The Unified messaging named property types
 * Class identifier: 442858e-a9e3-4e80-b900-317a210cc15b (PSETID_UnifiedMessaging)
 */
libfmapi_named_property_type_t libfmapi_unified_messaging_named_properties[ ] = {
	{ 13, "UMAudioNotes",							0x001e,	"PidNameAudioNotes",		"Audio notes" },

	{ (size_t) -1, NULL, (uint32_t) -1, "_UNKNOWN_", "Unknown" } };

/* Retrieves a string containing the property type identifier
 */
const char *libfmapi_property_types_get_identifier(
             libfmapi_property_type_t libfmapi_property_types[],
             uint32_t entry_type,
             uint32_t value_type )
{
	int iterator = 0;

	if( value_type == 0x001f )
	{
		value_type = 0x001e;
	}
	else if( value_type == 0x101f )
	{
		value_type = 0x101e;
	}
	while( ( libfmapi_property_types[ iterator ] ).entry_type != (uint32_t) -1 )
	{
		if( ( ( libfmapi_property_types[ iterator ] ).entry_type == entry_type )
		 && ( ( libfmapi_property_types[ iterator ] ).value_type == value_type ) )
		{
			break;
		}
		iterator++;
	}
	return(
	 ( libfmapi_property_types[ iterator ] ).identifier );
}

/* Retrieves a string containing the property type identifier
 */
const char *libfmapi_property_type_get_identifier(
	     uint8_t *class_identifier,
	     uint32_t entry_type,
	     uint32_t value_type )
{
	if( class_identifier == NULL )
	{
		if( entry_type == 0x0000 )
		{
			return( "PidTagNull" );
		}
		else if( ( entry_type >= 0x0001 )
		      && ( entry_type <= 0x0bff ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_message_envelope_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x0c00 )
		      && ( entry_type <= 0x0dff ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_recipient_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x0e00 )
		      && ( entry_type <= 0x0fff ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_non_transmittable_message_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x1000 )
		      && ( entry_type <= 0x2fff ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_message_content_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x3000 )
		      && ( entry_type <= 0x32ff ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_common_object_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x3300 )
		      && ( entry_type <= 0x33ff ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_form_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x3400 )
		      && ( entry_type <= 0x35ff ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_message_store_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x3600 )
		      && ( entry_type <= 0x36ff ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_folder_and_address_book_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x3700 )
		      && ( entry_type <= 0x38ff ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_attachment_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x3900 )
		      && ( entry_type <= 0x39ff ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_address_book_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x3a00 )
		      && ( entry_type <= 0x3bff ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_messaging_user_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x3c00 )
		      && ( entry_type <= 0x3cff ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_distribution_list_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x3d00 )
		      && ( entry_type <= 0x3dff ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_profile_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x3e00 )
		      && ( entry_type <= 0x3fff ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_status_object_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x4000 )
		      && ( entry_type <= 0x57ff ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_transport_provider_message_envelope_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x5800 )
		      && ( entry_type <= 0x5fff ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_transport_provider_recipient_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x6000 )
		      && ( entry_type <= 0x65ff ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_client_non_transmittable_message_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x6600 )
		      && ( entry_type <= 0x67ef ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_service_provider_non_transmittable_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x67f0 )
		      && ( entry_type <= 0x67ff ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_secure_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x6800 )
		      && ( entry_type <= 0x7bff ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_custom_message_content_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x7c00 )
		      && ( entry_type <= 0x7fff ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_custom_message_non_transmittable_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x8000 )
		      && ( entry_type <= 0xfffe ) )
		{
			return( libfmapi_property_types_get_identifier(
				 libfmapi_custom_named_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( entry_type == 0xffff )
		{
			return( "PROP_ID_INVALID" );
		}
	}
	else if( memory_compare(
	          class_identifier,
	          libfmapi_class_identifier_calendar,
	          16 ) == 0 )
	{
		return( libfmapi_property_types_get_identifier(
			 libfmapi_calendar_long_properties,
			 entry_type,
			 value_type ) );
	}
	else if( memory_compare(
	          class_identifier,
	          libfmapi_class_identifier_address,
	          16 ) == 0 )
	{
		return( libfmapi_property_types_get_identifier(
			 libfmapi_address_long_properties,
			 entry_type,
			 value_type ) );
	}
	else if( memory_compare(
	          class_identifier,
	          libfmapi_class_identifier_task,
	          16 ) == 0 )
	{
		return( libfmapi_property_types_get_identifier(
			 libfmapi_task_long_properties,
			 entry_type,
			 value_type ) );
	}
	else if( memory_compare(
	          class_identifier,
	          libfmapi_class_identifier_appointment,
	          16 ) == 0 )
	{
		return( libfmapi_property_types_get_identifier(
			 libfmapi_appointment_long_properties,
			 entry_type,
			 value_type ) );
	}
	else if( memory_compare(
	          class_identifier,
	          libfmapi_class_identifier_common,
	          16 ) == 0 )
	{
		return( libfmapi_property_types_get_identifier(
			 libfmapi_common_long_properties,
			 entry_type,
			 value_type ) );
	}
	else if( memory_compare(
	          class_identifier,
	          libfmapi_class_identifier_journal,
	          16 ) == 0 )
	{
		return( libfmapi_property_types_get_identifier(
			 libfmapi_journal_long_properties,
			 entry_type,
			 value_type ) );
	}
	else if( memory_compare(
	          class_identifier,
	          libfmapi_class_identifier_rss_feed,
	          16 ) == 0 )
	{
		return( libfmapi_property_types_get_identifier(
			 libfmapi_rss_feed_long_properties,
			 entry_type,
			 value_type ) );
	}
	else if( memory_compare(
	          class_identifier,
	          libfmapi_class_identifier_sharing,
	          16 ) == 0 )
	{
		return( libfmapi_property_types_get_identifier(
			 libfmapi_sharing_long_properties,
			 entry_type,
			 value_type ) );
	}
	else if( memory_compare(
	          class_identifier,
	          libfmapi_class_identifier_sticky_note,
	          16 ) == 0 )
	{
		return( libfmapi_property_types_get_identifier(
			 libfmapi_sticky_note_long_properties,
			 entry_type,
			 value_type ) );
	}
	else if( memory_compare(
	          class_identifier,
	          libfmapi_class_identifier_public_strings,
	          16 ) == 0 )
	{
		return( libfmapi_property_types_get_identifier(
			 libfmapi_public_strings_long_properties,
			 entry_type,
			 value_type ) );
	}
	return( "_UNKNOWN_" );
}

/* Retrieves a string containing the property type description
 */
const char *libfmapi_property_types_get_description(
             libfmapi_property_type_t libfmapi_property_types[],
             uint32_t entry_type,
             uint32_t value_type )
{
	int iterator = 0;

	if( value_type == 0x001f )
	{
		value_type = 0x001e;
	}
	else if( value_type == 0x101f )
	{
		value_type = 0x101e;
	}
	while( ( libfmapi_property_types[ iterator ] ).entry_type != (uint32_t) -1 )
	{
		if( ( ( libfmapi_property_types[ iterator ] ).entry_type == entry_type )
		 && ( ( libfmapi_property_types[ iterator ] ).value_type == value_type ) )
		{
			break;
		}
		iterator++;
	}
	return(
	 ( libfmapi_property_types[ iterator ] ).description );
}

/* Retrieves a string containing the property type description
 */
const char *libfmapi_property_type_get_description(
             uint8_t *class_identifier,
             uint32_t entry_type,
             uint32_t value_type )
{
	if( class_identifier == NULL )
	{
		if( entry_type == 0x0000 )
		{
			return( "NULL" );
		}
		else if( ( entry_type >= 0x0001 )
		      && ( entry_type <= 0x0bff ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_message_envelope_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x0c00 )
		      && ( entry_type <= 0x0dff ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_recipient_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x0e00 )
		      && ( entry_type <= 0x0fff ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_non_transmittable_message_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x1000 )
		      && ( entry_type <= 0x2fff ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_message_content_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x3000 )
		      && ( entry_type <= 0x33ff ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_common_object_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x3400 )
		      && ( entry_type <= 0x35ff ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_message_store_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x3600 )
		      && ( entry_type <= 0x36ff ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_folder_and_address_book_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x3700 )
		      && ( entry_type <= 0x38ff ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_attachment_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x3900 )
		      && ( entry_type <= 0x39ff ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_address_book_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x3a00 )
		      && ( entry_type <= 0x3bff ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_messaging_user_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x3c00 )
		      && ( entry_type <= 0x3cff ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_distribution_list_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x3d00 )
		      && ( entry_type <= 0x3dff ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_profile_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x3e00 )
		      && ( entry_type <= 0x3fff ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_status_object_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x4000 )
		      && ( entry_type <= 0x57ff ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_transport_provider_message_envelope_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x5800 )
		      && ( entry_type <= 0x5fff ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_transport_provider_recipient_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x6000 )
		      && ( entry_type <= 0x65ff ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_client_non_transmittable_message_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x6600 )
		      && ( entry_type <= 0x67ef ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_service_provider_non_transmittable_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x67f0 )
		      && ( entry_type <= 0x67ff ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_secure_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x6800 )
		      && ( entry_type <= 0x7bff ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_custom_message_content_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x7c00 )
		      && ( entry_type <= 0x7fff ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_custom_message_non_transmittable_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( ( entry_type >= 0x8000 )
		      && ( entry_type <= 0xfffe ) )
		{
			return( libfmapi_property_types_get_description(
				 libfmapi_custom_named_property_types,
				 entry_type,
				 value_type ) );
		}
		else if( entry_type == 0xffff )
		{
			return( "Invalid property" );
		}
	}
	else if( memory_compare(
	          class_identifier,
	          libfmapi_class_identifier_calendar,
	          16 ) == 0 )
	{
		return( libfmapi_property_types_get_description(
			 libfmapi_calendar_long_properties,
			 entry_type,
			 value_type ) );
	}
	else if( memory_compare(
	          class_identifier,
	          libfmapi_class_identifier_address,
	          16 ) == 0 )
	{
		return( libfmapi_property_types_get_description(
			 libfmapi_address_long_properties,
			 entry_type,
			 value_type ) );
	}
	else if( memory_compare(
	          class_identifier,
	          libfmapi_class_identifier_task,
	          16 ) == 0 )
	{
		return( libfmapi_property_types_get_description(
			 libfmapi_task_long_properties,
			 entry_type,
			 value_type ) );
	}
	else if( memory_compare(
	          class_identifier,
	          libfmapi_class_identifier_appointment,
	          16 ) == 0 )
	{
		return( libfmapi_property_types_get_description(
			 libfmapi_appointment_long_properties,
			 entry_type,
			 value_type ) );
	}
	else if( memory_compare(
	          class_identifier,
	          libfmapi_class_identifier_common,
	          16 ) == 0 )
	{
		return( libfmapi_property_types_get_description(
			 libfmapi_common_long_properties,
			 entry_type,
			 value_type ) );
	}
	else if( memory_compare(
	          class_identifier,
	          libfmapi_class_identifier_journal,
	          16 ) == 0 )
	{
		return( libfmapi_property_types_get_description(
			 libfmapi_journal_long_properties,
			 entry_type,
			 value_type ) );
	}
	else if( memory_compare(
	          class_identifier,
	          libfmapi_class_identifier_rss_feed,
	          16 ) == 0 )
	{
		return( libfmapi_property_types_get_description(
			 libfmapi_rss_feed_long_properties,
			 entry_type,
			 value_type ) );
	}
	else if( memory_compare(
	          class_identifier,
	          libfmapi_class_identifier_sharing,
	          16 ) == 0 )
	{
		return( libfmapi_property_types_get_description(
			 libfmapi_sharing_long_properties,
			 entry_type,
			 value_type ) );
	}
	else if( memory_compare(
	          class_identifier,
	          libfmapi_class_identifier_sticky_note,
	          16 ) == 0 )
	{
		return( libfmapi_property_types_get_description(
			 libfmapi_sticky_note_long_properties,
			 entry_type,
			 value_type ) );
	}
	else if( memory_compare(
	          class_identifier,
	          libfmapi_class_identifier_public_strings,
	          16 ) == 0 )
	{
		return( libfmapi_property_types_get_description(
			 libfmapi_public_strings_long_properties,
			 entry_type,
			 value_type ) );
	}
	return( "Unknown" );
}

/* Retrieves a string containing the named property type identifier
 */
const char *libfmapi_named_property_types_get_identifier(
             libfmapi_named_property_type_t libfmapi_named_property_types[],
             const char *name,
             size_t name_size,
             uint32_t value_type )
{
	int iterator = 0;

	if( value_type == 0x001f )
	{
		value_type = 0x001e;
	}
	else if( value_type == 0x101f )
	{
		value_type = 0x101e;
	}
	while( ( libfmapi_named_property_types[ iterator ] ).name != NULL )
	{
		if( ( ( libfmapi_named_property_types[ iterator ] ).name_size == name_size )
		 && ( narrow_string_compare_no_case(
		       ( libfmapi_named_property_types[ iterator ] ).name,
		       name,
		       name_size ) == 0 ) )
		{
			break;
		}
		iterator++;
	}
	return(
	 ( libfmapi_named_property_types[ iterator ] ).identifier );
}

/* Retrieves a string containing the named property type identifier
 */
const char *libfmapi_named_property_type_get_identifier(
             uint8_t *class_identifier,
             const char *name,
             size_t name_size,
             uint32_t value_type )
{
	if( class_identifier != NULL )
	{
		if( memory_compare(
		     class_identifier,
		     libfmapi_class_identifier_public_strings,
		     16 ) == 0 )
		{
			return( libfmapi_named_property_types_get_identifier(
				 libfmapi_public_strings_named_properties,
				 name,
				 name_size,
				 value_type ) );
		}
		else if( memory_compare(
		          class_identifier,
		          libfmapi_class_identifier_internet_headers,
		          16 ) == 0 )
		{
			return( libfmapi_named_property_types_get_identifier(
				 libfmapi_internet_headers_named_properties,
				 name,
				 name_size,
				 value_type ) );
		}
		else if( memory_compare(
		          class_identifier,
		          libfmapi_class_identifier_attachment,
		          16 ) == 0 )
		{
			return( libfmapi_named_property_types_get_identifier(
				 libfmapi_attachment_named_properties,
				 name,
				 name_size,
				 value_type ) );
		}
		else if( memory_compare(
		          class_identifier,
		          libfmapi_class_identifier_unified_messaging,
		          16 ) == 0 )
		{
			return( libfmapi_named_property_types_get_identifier(
				 libfmapi_unified_messaging_named_properties,
				 name,
				 name_size,
				 value_type ) );
		}
	}
	return( "_UNKNOWN_" );
}

/* Retrieves a string containing the named property type description
 */
const char *libfmapi_named_property_types_get_description(
             libfmapi_named_property_type_t libfmapi_named_property_types[],
             const char *name,
             size_t name_size,
             uint32_t value_type )
{
	int iterator = 0;

	if( value_type == 0x001f )
	{
		value_type = 0x001e;
	}
	else if( value_type == 0x101f )
	{
		value_type = 0x101e;
	}
	while( ( libfmapi_named_property_types[ iterator ] ).name != NULL )
	{
		if( ( ( libfmapi_named_property_types[ iterator ] ).name_size == name_size )
		 && ( narrow_string_compare_no_case(
		       ( libfmapi_named_property_types[ iterator ] ).name,
		       name,
		       name_size ) == 0 ) )
		{
			break;
		}
		iterator++;
	}
	return(
	 ( libfmapi_named_property_types[ iterator ] ).description );
}

/* Retrieves a string containing the named property type description
 */
const char *libfmapi_named_property_type_get_description(
             uint8_t *class_identifier,
             const char *name,
             size_t name_size,
             uint32_t value_type )
{
	if( class_identifier != NULL )
	{
		if( memory_compare(
		     class_identifier,
		     libfmapi_class_identifier_public_strings,
		     16 ) == 0 )
		{
			return( libfmapi_named_property_types_get_description(
				 libfmapi_public_strings_named_properties,
				 name,
				 name_size,
				 value_type ) );
		}
		else if( memory_compare(
		          class_identifier,
		          libfmapi_class_identifier_internet_headers,
		          16 ) == 0 )
		{
			return( libfmapi_named_property_types_get_description(
				 libfmapi_internet_headers_named_properties,
				 name,
				 name_size,
				 value_type ) );
		}
		else if( memory_compare(
		          class_identifier,
		          libfmapi_class_identifier_attachment,
		          16 ) == 0 )
		{
			return( libfmapi_named_property_types_get_description(
				 libfmapi_attachment_named_properties,
				 name,
				 name_size,
				 value_type ) );
		}
		else if( memory_compare(
		          class_identifier,
		          libfmapi_class_identifier_unified_messaging,
		          16 ) == 0 )
		{
			return( libfmapi_named_property_types_get_description(
				 libfmapi_unified_messaging_named_properties,
				 name,
				 name_size,
				 value_type ) );
		}
	}
	return( "_UNKNOWN_" );
}

#endif

