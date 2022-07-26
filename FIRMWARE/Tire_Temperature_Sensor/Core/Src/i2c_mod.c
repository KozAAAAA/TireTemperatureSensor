/*
 * hal_i2c_mod.c
 *
 *  Created on: Jul 26, 2022
 *      Author: mateusz
 */


HAL_StatusTypeDef Custom_HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress,

										  uint8_t command, uint8_t startAddress, uint8_t addressStep, uint8_t nMemAddressRead,

										  uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  uint32_t tickstart;

  /* Check the parameters */
  //assert_param(IS_I2C_MEMADD_SIZE(MemAddSize));

  if (hi2c->State == HAL_I2C_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      hi2c->ErrorCode = HAL_I2C_ERROR_INVALID_PARAM;
      return  HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(hi2c);

    /* Init tickstart for timeout management*/
    tickstart = HAL_GetTick();

    if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, I2C_TIMEOUT_BUSY, tickstart) != HAL_OK)
    {
      return HAL_ERROR;
    }

    hi2c->State     = HAL_I2C_STATE_BUSY_RX;
    hi2c->Mode      = HAL_I2C_MODE_MEM;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

    /* Prepare transfer parameters */
    hi2c->pBuffPtr  = pData;
    hi2c->XferCount = Size;
    hi2c->XferISR   = NULL;

    /* Send Slave Address and Memory Address */
    if(Custom_I2C_RequestMemoryRead(hi2c, DevAddress,

    								command, startAddress,
									addressStep, nMemAddressRead,

									Timeout, tickstart) != HAL_OK)
    {
        /* Process Unlocked */
        __HAL_UNLOCK(hi2c);
        return HAL_ERROR;
    }


    /* Send Slave Address */
    /* Set NBYTES to write and reload if hi2c->XferCount > MAX_NBYTE_SIZE and generate RESTART */
    if (hi2c->XferCount > MAX_NBYTE_SIZE)
    {
      hi2c->XferSize = MAX_NBYTE_SIZE;
      I2C_TransferConfig(hi2c, DevAddress, (uint8_t)hi2c->XferSize, I2C_RELOAD_MODE,
                         I2C_GENERATE_START_READ);
    }
    else
    {
      hi2c->XferSize = hi2c->XferCount;
      I2C_TransferConfig(hi2c, DevAddress, (uint8_t)hi2c->XferSize, I2C_AUTOEND_MODE,
                         I2C_GENERATE_START_READ);
    }

    do
    {
      /* Wait until RXNE flag is set */
      if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_RXNE, RESET, Timeout, tickstart) != HAL_OK)
      {
        return HAL_ERROR;
      }

      /* Read data from RXDR */
      *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->RXDR;

      /* Increment Buffer pointer */
      hi2c->pBuffPtr++;

      hi2c->XferSize--;
      hi2c->XferCount--;

      if ((hi2c->XferCount != 0U) && (hi2c->XferSize == 0U))
      {
        /* Wait until TCR flag is set */
        if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_TCR, RESET, Timeout, tickstart) != HAL_OK)
        {
          return HAL_ERROR;
        }

        if (hi2c->XferCount > MAX_NBYTE_SIZE)
        {
          hi2c->XferSize = MAX_NBYTE_SIZE;
          I2C_TransferConfig(hi2c, DevAddress, (uint8_t) hi2c->XferSize, I2C_RELOAD_MODE,
                             I2C_NO_STARTSTOP);
        }
        else
        {
          hi2c->XferSize = hi2c->XferCount;
          I2C_TransferConfig(hi2c, DevAddress, (uint8_t)hi2c->XferSize, I2C_AUTOEND_MODE,
                             I2C_NO_STARTSTOP);
        }
      }
    } while (hi2c->XferCount > 0U);

    /* No need to Check TC flag, with AUTOEND mode the stop is automatically generated */
    /* Wait until STOPF flag is reset */
    if (I2C_WaitOnSTOPFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /* Clear STOP Flag */
    __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_STOPF);

    /* Clear Configuration Register 2 */
    I2C_RESET_CR2(hi2c);

    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode  = HAL_I2C_MODE_NONE;

    /* Process Unlocked */
    __HAL_UNLOCK(hi2c);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

static HAL_StatusTypeDef Custom_I2C_RequestMemoryRead(I2C_HandleTypeDef *hi2c, uint16_t DevAddress,
																												//num_of_2Bytes_reads_from_mem
                                               uint8_t command, uint8_t startAddress, uint8_t addressStep, uint8_t nMemAddressRead,

											   uint32_t Timeout, uint32_t Tickstart)
{

									//The_num_of_bytes
  I2C_TransferConfig(hi2c, DevAddress, (uint8_t)4, I2C_SOFTEND_MODE, I2C_GENERATE_START_WRITE);

  /* Wait until TXIS flag is set */
  if (I2C_WaitOnTXISFlagUntilTimeout(hi2c, Timeout, Tickstart) != HAL_OK)
  {
    return HAL_ERROR;
  }

// "mem_write"
  hi2c->Instance->TXDR = I2C_MEM_ADD_LSB(command);


  if (I2C_WaitOnTXISFlagUntilTimeout(hi2c, Timeout, Tickstart) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hi2c->Instance->TXDR = I2C_MEM_ADD_LSB(startAddress);


  if (I2C_WaitOnTXISFlagUntilTimeout(hi2c, Timeout, Tickstart) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hi2c->Instance->TXDR = I2C_MEM_ADD_LSB(addressStep);


  if (I2C_WaitOnTXISFlagUntilTimeout(hi2c, Timeout, Tickstart) != HAL_OK)
  {
    return HAL_ERROR;
  }
  hi2c->Instance->TXDR = I2C_MEM_ADD_LSB(nMemAddressRead);
//

  /* Wait until [Transfer Complete] flag is set */
  if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_TC, RESET, Timeout, Tickstart) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}



