
long checkSaveAndExit()
{
	//�m�F�_�C�A���O
	WSCmessageDialog* msg = WSGIappMessageDialog(); //A
	msg->setProperty(WSNwidth,500);
	msg->setProperty(WSNno,True);
	msg->setProperty(WSNdefaultPosition,True);
	msg->setProperty(WSNlabelString,
		"Exit and save data?\n If you do not want to save and exit,push NO...");
	//�_�C�A���O�̕\��
	long ret = msg->popup(); //B

	return ret;
}
