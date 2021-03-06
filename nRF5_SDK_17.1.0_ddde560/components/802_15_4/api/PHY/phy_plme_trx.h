/**
 * Copyright (c) 2016 - 2021 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 *
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef PHY_PLME_TRX_H_INCLUDED
#define PHY_PLME_TRX_H_INCLUDED

#include <stdint.h>
#include "phy_common.h"

/** @file
 * This file contains declarations of PHY TRX routines and necessary types.
 *
 * @defgroup phy_trx PHY TRX API
 * @ingroup phy_15_4
 * @{
 * @brief Module to declare PHY Transceiver State API
 * @details The PHY TRX module declares Transceiver state change PHY routines and necessary types according to
 * the PHY specification. More specifically, PHY set TRX state request plme_set_trx_state_req(),
 * PHY TRX state change confirm plme_set_trx_state_conf() primitives are declared. An additional
 * primitive not covered by the standard is declared. This is plme_set_trx_state() which is a synchronous
 * version of plme_set_trx_state_req().
 */

/**
 * @brief   PLME-SET_TRX_STATE.request parameters.
 *
 * @details The PLME-SET_TRX_STATE.request primitive is generated
 *          by the next higher layer of a device and issued to its PLME to
 *          set transmitter status.
 *
 *          In accordance with IEEE Std 802.15.4-2006, section 6.2.2.7.1
 */
typedef struct
{
    /** One of PHY_RX_ON, PHY_TRX_OFF, PHY_FORCE_TRX_OFF, PHY_TX_ON or PHY_FORCE_TX_ON. */
    phy_enum_t state;
} plme_trx_req_t;


/**
 * @brief   PLME-TRX.confirm parameters.
 *
 * @details The PLME-TRX.confirm primitive is generated by
 *          PLME and issued to its next higher layer in response to
 *          an PLME-SET_TRX_STATE.request primitive.
 *
 *          In accordance with IEEE Std 802.15.4-2006, section 6.2.2.8.1
 */
typedef struct
{
    /** Holds result of trx state change request.
     *
     *  @details Equals to PHY_SUCCESS if state changed successfully
     *  or current PHY state in either case.
     */
    phy_enum_t status;
} plme_trx_conf_t;


/**@brief   PLME-SET_TRX_STATE request.
 *
 * @details Request PHY to change internal operating state.
 *          In accordance with IEEE Std 802.15.4-2006, section 6.2.2.7
 *
 * @param[in] req Pointer to PLME-SET_TRX_STATE.request parameters. 
 *                See @ref plme_trx_req_t.
 */
void plme_set_trx_state_req(plme_trx_req_t * req);


/**@brief   PLME-SET_TRX_STATE.confirm callback function, implemented by the next higher layer.
 *
 * @details The PLME-SET_TRX_STATE.confirm primitive is generated
 *          by the PLME and issued to its next higher layer in response to
 *          an PLME-SET_TRX_STATE.request primitive.
 *
 *          In accordance with IEEE Std 802.15.4-2006, section 6.2.2.8
 *
 * @param[out] conf Pointer to PLME-TRX.confirm parameters. See @ref plme_trx_conf_t.
 */
void plme_set_trx_state_conf(plme_trx_conf_t * conf);


/**@brief   Direct (synchronous) PLME-SET_TRX_STATE  access.
 *
 * @details Optional. Not covered by the standard.

 * @param[in] state One of PHY_RX_ON, PHY_TRX_OFF, PHY_FORCE_TRX_OFF or PHY_TX_ON.
 *
 * @return  PHY_SUCCESS if state changed successfully or current PHY state
 *          in either case.
 */
phy_enum_t plme_set_trx_state(phy_enum_t state);

/** @} */

#endif // PHY_PLME_TRX_H_INCLUDED
