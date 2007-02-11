
long checkSaveAndExit()
{
	//確認ダイアログ
	WSCmessageDialog* msg = WSGIappMessageDialog(); //A
	msg->setProperty(WSNwidth,500);
	msg->setProperty(WSNno,True);
	msg->setProperty(WSNdefaultPosition,True);
	msg->setProperty(WSNlabelString,
		"Exit and save data?\n If you do not want to save and exit,push NO...");
	//ダイアログの表示
	long ret = msg->popup(); //B

	return ret;
}
