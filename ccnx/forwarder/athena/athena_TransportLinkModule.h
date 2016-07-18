/*
 * Copyright (c) 2015-2016, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX OR PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ################################################################################
 * #
 * # PATENT NOTICE
 * #
 * # This software is distributed under the BSD 2-clause License (see LICENSE
 * # file).  This BSD License does not make any patent claims and as such, does
 * # not act as a patent grant.  The purpose of this section is for each contributor
 * # to define their intentions with respect to intellectual property.
 * #
 * # Each contributor to this source code is encouraged to state their patent
 * # claims and licensing mechanisms for any contributions made. At the end of
 * # this section contributors may each make their own statements.  Contributor's
 * # claims and grants only apply to the pieces (source code, programs, text,
 * # media, etc) that they have contributed directly to this software.
 * #
 * # There is no guarantee that this section is complete, up to date or accurate. It
 * # is up to the contributors to maintain their portion of this section and up to
 * # the user of the software to verify any claims herein.
 * #
 * # Do not remove this header notification.  The contents of this section must be
 * # present in all distributions of the software.  You may only modify your own
 * # intellectual property statements.  Please provide contact information.
 *
 * - Palo Alto Research Center, Inc
 * This software distribution does not grant any rights to patents owned by Palo
 * Alto Research Center, Inc (PARC). Rights to these patents are available via
 * various mechanisms. As of January 2016 PARC has committed to FRAND licensing any
 * intellectual property used by its contributions to this software. You may
 * contact PARC at cipo@parc.com for more information or visit http://www.ccnx.org
 */
/**
 * @author Kevin Fox, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2015-2016, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#ifndef libathena_TransportLinkModule_h
#define libathena_TransportLinkModule_h

#include <parc/logging/parc_Log.h>
#include <parc/algol/parc_ArrayList.h>
#include <parc/algol/parc_FileOutputStream.h>
#include <parc/logging/parc_Log.h>

#include <ccnx/forwarder/athena/athena_TransportLink.h>

/**
 * @typedef AthenaTransportLinkModule
 * @brief Link Specific Module
 */
typedef struct AthenaTransportLinkModule AthenaTransportLinkModule;

/**
 * @typedef AthenaTransportLinkModule_Open
 * @brief Link Specific Module Open method
 */
typedef AthenaTransportLink *(AthenaTransportLinkModule_Open)(struct AthenaTransportLinkModule *athenaTransportLinkModule, PARCURI *connectionURI);

/**
 * @typedef AthenaTransportLinkModule_Poll
 * @brief Link Specific Module Poll method
 */
typedef int (AthenaTransportLinkModule_Poll)(struct AthenaTransportLink *athenaTransportLink, int timeout);

/**
 * @typedef AthenaTransportLinkModule_AddLinkCallback
 * @brief Link Specific Module Add Link Callback method
 */
typedef int (AthenaTransportLinkModule_AddLinkCallback)(void *, struct AthenaTransportLink *athenaTransportLink);

/**
 * @typedef AthenaTransportLinkModule_AddLinkCallbackContext
 * @brief Link Specific Module Add Link Callback method private context
 */
typedef void *AthenaTransportLinkModule_AddLinkCallbackContext;

/**
 * @typedef AthenaTransportLinkModule_RemoveLinkCallback
 * @brief Link Specific Module Remove Link Callback method
 */
typedef void (AthenaTransportLinkModule_RemoveLinkCallback)(void *, struct AthenaTransportLink *athenaTransportLink);

/**
 * @typedef AthenaTransportLinkModule_RemoveLinkCallbackContext
 * @brief Link Specific Module Remove Link Callback method private context
 */
typedef void *AthenaTransportLinkModule_RemoveLinkCallbackContext;

/**
 * @abstract create a new Link Module instance
 * @discussion
 *
 * @param [in] name of new link module
 * @param [in] open callback method
 * @param [in] poll callback method
 * @return new instance on on success, NULL on error.
 *
 * Example:
 * @code
 * {
 * }
 * @endcode
 */
AthenaTransportLinkModule *athenaTransportLinkModule_Create(const char *name,
                                                            AthenaTransportLinkModule_Open *open,
                                                            AthenaTransportLinkModule_Poll *poll);

/**
 * @abstract destroy a Link Module
 * @discussion
 *
 * @param [in] athenaTransportLinkAdapter link module instance to destroy
 *
 * Example:
 * @code
 * {
 * }
 * @endcode
 */
void athenaTransportLinkModule_Destroy(AthenaTransportLinkModule **);

/**
 * @abstract obtain a pointer to the logger
 * @discussion
 *
 * @return pointer to logging facility
 *
 * Example:
 * @code
 * void
 * {
 *     PARCLog *log = athenaTransportLinkModule_GetLogger(athenaTransportLinkModule);
 * }
 * @endcode
 */
PARCLog *athenaTransportLinkModule_GetLogger(AthenaTransportLinkModule *athenaTransportLinkModule);

/**
 * @abstract open a new link instance
 * @discussion
 *
 * @param [in] athenaTransportLinkModule module instance to instantiate link
 * @param [in] connectionURI link connection URI specification
 * @return pointer to new link instance
 *
 * Example:
 * @code
 * {
 * }
 * @endcode
 */
AthenaTransportLink *athenaTransportLinkModule_Open(AthenaTransportLinkModule *athenaTransportLinkModule, PARCURI *connectionURI);

/**
 * @abstract poll the module to mark link events
 * @discussion
 *
 * @param [in] athenaTransportLinkModule module instance to poll
 * @param [in] timeout number of milli-seconds to wait, -1 to wait forever
 * @return number of new events registered
 *
 * Example:
 * @code
 * {
 * }
 * @endcode
 */
int athenaTransportLinkModule_Poll(AthenaTransportLinkModule *athenaTransportLinkModule, int timeout);

/**
 * @abstract get the name of the link module
 * @discussion
 *
 * @param [in] athenaTransportLinkModule module instance to query
 * @return name of module
 *
 * Example:
 * @code
 * {
 * }
 * @endcode
 */
const char *athenaTransportLinkModule_GetName(AthenaTransportLinkModule *athenaTransportLinkModule);

/**
 * @abstract register remove link callbacks
 * @discussion
 *
 * @param [in] athenaTransportLinkModule link module instance
 * @param [in] removeLink callback
 * @param [in] removeLink callback context
 *
 * Example:
 * @code
 * {
 *
 * }
 * @endcode
 */
void athenaTransportLinkModule_SetRemoveLinkCallback(AthenaTransportLinkModule *athenaTransportLinkModule,
                                                     AthenaTransportLinkModule_RemoveLinkCallback *removeLink,
                                                     AthenaTransportLinkModule_RemoveLinkCallbackContext removeLinkContext);

/**
 * @abstract register add link callbacks
 * @discussion
 *
 * @param [in] athenaTransportLinkModule link module instance
 * @param [in] addLink callback
 * @param [in] addLink callback context
 *
 * Example:
 * @code
 * {
 *
 * }
 * @endcode
 */
void athenaTransportLinkModule_SetAddLinkCallback(AthenaTransportLinkModule *athenaTransportLinkModule,
                                                  AthenaTransportLinkModule_AddLinkCallback *addLink,
                                                  AthenaTransportLinkModule_AddLinkCallbackContext addLinkContext);

/**
 * Set the logging level for a module
 *
 * @param athenaTransportLinkModule instance
 * @param level to set logging to (see PARCLog)
 */
void athenaTransportLinkModule_SetLogLevel(AthenaTransportLinkModule *athenaTransportLinkModule, const PARCLogLevel level);

PARCBuffer *athenaTransportLinkModule_CreateMessageBuffer(CCNxMetaMessage *message);

CCNxCodecNetworkBufferIoVec *athenaTransportLinkModule_GetMessageIoVector(CCNxMetaMessage *message);

#endif // libathena_TransportLinkModule_h
