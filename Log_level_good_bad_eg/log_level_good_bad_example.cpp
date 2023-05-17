
void MqReciever::onHandleMessageFromMq(const char* data, const int nSize)
{
    /*
     * BAD: If error happen (e.g: decoder can not decode)
     * In validation/production, this logv is never printed out
     * developer won't able to know which point has the failure
     */
    if(!m_decoder.startDecording(data, nSize))
    {
        logv(TAG, "faild: startDecording(). mq=%s, mqdest=%d, size=%d", m_mqname, m_mqdes, nSize);
        return;
    }
}

void MqReciever::onHandleMessageFromMq(const char* data, const int nSize)
{
    if(!m_decoder.startDecording(data, nSize))
    {
        loge(TAG, "faild: startDecording(). mq=%s, mqdest=%d, size=%d", m_mqname, m_mqdes, nSize);
        return;
    }
    /*
     * GOOD: Use logv too show name of the receiver, which is usually not too important in normal debug
     * But this logv is very good for a deeper debug session from the base framnework
     */
    logv(TAG, "#Receiver: %s", m_mqname);
    m_decoder.trace(m_mqname, m_curofmsg, m_numofmsg);
}


bool BaseReceiver::onHandleMessageFromMq(MsgDecoder& decoder)
{  
    /*
     * GOOD: Use logv to print the log for the good case and don't need this in normal debug
     */
    if(m_aListener[i]->onHandleMessages(decoder))
    {
        logv(TAG, "End %d.%s from %s", decoder.getCmd(), decoder.getFunction(), decoder.getFromPath());
        return true;
    }
    // fail
    else
    {
        loge(TAG, "failed in handling a message(%d,%s).", decoder.getCmd(), decoder.getFunction());
        return false;
    }
}

bool BaseReceiver::onHandleMessageFromMq(MsgDecoder& decoder)
{  
    if(m_aListener[i]->onHandleMessages(decoder))
    {
        logv(TAG, "End %d.%s from %s", decoder.getCmd(), decoder.getFunction(), decoder.getFromPath());
        return true;
    }
    // fail
    else
    {
        /*
        * BAD: Use logv to print the log for the failure case
        */
        logv(TAG, "failed in handling a message(%d,%s).", decoder.getCmd(), decoder.getFunction());
        return false;
    }
}


bool BrokerProxy::ackServiceConnection(const BROKER_MSG_T& tMsg)
{
    /*
     * BAD: Use logv to let user know when the function is called
     */
    logv(TAG, "==>ackServiceConnection(%s)", tMsg.service);

    if(!sendMessage(BROKER_MSG_ACK_REGISTER_SERVICE, &tMsg, (int)sizeof(tMsg)))
    {
        return false;
    }

    return true;
}

void dumpBuffer(const BUFF_T &tBuff)
{
    /*
     * GOOD: Use logv when need to dump a buffer which has much information
     * Note: 2 logv below used to print out dumped info from buffer
     */
    logv(TAG, "# dumpBuffer-0x%x/0x%x,0x%x/0x%x,0x%x,0x%x", tBuff.aData[0], tBuff.aData[1],
                                            tBuff.aData[2], tBuff.aData[3], tBuff.aData[4], tBuff.aData[5]);
    for (int i = 0; i < tBuff.nSize; i++)
    {
        logv(TAG, "#- buff[%d] = 0x%x", i, tBuff.aData[i]);
    }
    return;
}


#define CL_SWUPGRADE 0


int CmdDeploy::sendToSwupgrade(const MSG_T &tMsg)
{
    logv("Send to Swupgrade Service");
    onMessageReceived(tMsg, CL_SWUPGRADE);
    /*
     * BAD: Use logv to print return result of a function
     */
    logv("##SECURE BOOT RESULT - %d", tMsg->aData[0]);
    return tMsg->aData[0];
}
