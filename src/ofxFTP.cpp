#include "ofxFTP.h"

//
// client
//
ofxFTPClient::ofxFTPClient()
{
    ftpClient   = NULL;
    bVerbose    = false;
    host        = "";
    user        = "";
    pass        = "";
    port        = 0;
    bSetup      = false;
}
void ofxFTPClient::setup(string _host, int _port, string username, string password)
{
    host    = _host;
    user    = username;
    pass    = password;
    port    = _port;
    bSetup  = true;
}



int ofxFTPClient::sendFromOf(string fileName, string localFolder, string remoteFolder)
{
	if( bSetup == false ){
        if( bVerbose )printf("error - you need to call setup first\n");
        return -1;
    }
    
    int numBytes = 0;
    
    try{
        startFtpSesssion();
        
        if( bVerbose )printf("ftp-ing %s\n", fileName.c_str());
        
        localFolder = ofToDataPath( localFolder );
        
        //add slashes if they don't exist
        if(localFolder.length() > 0){
            if( localFolder[localFolder.length()-1] != '/' ){
                localFolder += "/";
            }
        }
        
        if(remoteFolder.length() > 0){
            if( remoteFolder[remoteFolder.length()-1] != '/' ){
                remoteFolder += "/";
            }
        }
        
        string localPath    = localFolder  + fileName;
        string remotePath   = remoteFolder + fileName;
        
        ostringstream remoteOSS;
        remoteOSS << remoteFolder << fileName;
        
        if( bVerbose )printf("localpath is %s\n remotepath is %s\n", localPath.c_str(), remotePath.c_str());
        
        ftpClient->setFileType(Poco::Net::FTPClientSession::TYPE_BINARY);
        
        ostream& ftpOStream = ftpClient->beginUpload(remoteOSS.str().c_str());  //how to make it overwrite?
        
        ifstream localIFStream(localPath.c_str(), ifstream::in | ifstream::binary);
        numBytes = Poco::StreamCopier::copyStream(localIFStream, ftpOStream);
        ftpClient->endUpload();
        
        endFtpSession();
        
        if(bVerbose)printf("uploaded %i bytes\n\n", numBytes);

		return numBytes;
        
    }
	catch ( Poco::Net::FTPException& e)
	{
		cout<< e.displayText() <<endl;
		return -1;
	}
	catch (Poco::Exception& exc)
	{
		cout << exc.displayText() << endl;
		return -1;
	}

    return numBytes;

}

int ofxFTPClient::getToOf(string fileName, string localFolder, string remoteFolder)
{
	if( bSetup == false ){
        if( bVerbose )printf("error - you need to call setup first\n");
        return -1;
    }
    
    int numBytes = 0;
    
    try{
        startFtpSesssion();
        
        if( bVerbose )printf("ftp-ing %s\n", fileName.c_str());
        
        localFolder = ofToDataPath( localFolder );
        
        //add slashes if they don't exist
        if(localFolder.length() > 0){
            if( localFolder[localFolder.length()-1] != '/' ){
                localFolder += "/";
            }
        }
        
        if(remoteFolder.length() > 0){
            if( remoteFolder[remoteFolder.length()-1] != '/' ){
                remoteFolder += "/";
            }
        }
        
        string localPath    = localFolder  + fileName;
        string remotePath   = remoteFolder + fileName;
        
        ostringstream remoteOSS;
        remoteOSS << remoteFolder << fileName;
        
        if( bVerbose )printf("localpath is %s\n remotepath is %s\n", localPath.c_str(), remotePath.c_str());
        
        ftpClient->setFileType(Poco::Net::FTPClientSession::TYPE_BINARY);
        istream& ftpOStream = ftpClient->beginDownload(remoteOSS.str().c_str());

        ofstream localIFStream(localPath.c_str(), ifstream::out | ifstream::binary);
        numBytes = Poco::StreamCopier::copyStream(ftpOStream, localIFStream);
        ftpClient->endDownload();
        endFtpSession();
        
        if(bVerbose)printf("downloaded %i bytes\n\n", numBytes);

		return numBytes;
        
    }
    catch ( Poco::Net::FTPException& e)
    {
        cout << e.displayText() << endl;
        return -1;
    }
	catch (Poco::Exception& exc)
	{
		cout << exc.displayText() << endl;
		return -1;
	}
}

int ofxFTPClient::send(string fileName, string localFolder, string remoteFolder)
{
	if( bSetup == false ){
		if( bVerbose )printf("error - you need to call setup first\n");
		return -1;
	}

	int numBytes = 0;

	try{
		startFtpSesssion();

		if( bVerbose )printf("ftp-ing %s\n", fileName.c_str());

		//localFolder = ofToDataPath( localFolder );

		//add slashes if they don't exist
		if(localFolder.length() > 0){
			if( localFolder[localFolder.length()-1] != '/' ){
				localFolder += "/";
			}
		}

		if(remoteFolder.length() > 0){
			if( remoteFolder[remoteFolder.length()-1] != '/' ){
				remoteFolder += "/";
			}
		}

		string localPath    = localFolder  + fileName;
		string remotePath   = remoteFolder + fileName;

		ostringstream remoteOSS;
		remoteOSS << remoteFolder << fileName;

		if( bVerbose )printf("localpath is %s\n remotepath is %s\n", localPath.c_str(), remotePath.c_str());

		ftpClient->setFileType(Poco::Net::FTPClientSession::TYPE_BINARY);

		ostream& ftpOStream = ftpClient->beginUpload(remoteOSS.str().c_str());  //how to make it overwrite?

		ifstream localIFStream(localPath.c_str(), ifstream::in | ifstream::binary);
		numBytes = Poco::StreamCopier::copyStream(localIFStream, ftpOStream);
		ftpClient->endUpload();

		endFtpSession();

		if(bVerbose)printf("uploaded %i bytes\n\n", numBytes);

		return numBytes;

	}
	catch ( Poco::Net::FTPException& e)
	{
		cout<< e.displayText() <<endl;
		return -1;
	}
	catch (Poco::Exception& exc)
	{
		cout << exc.displayText() << endl;
		return -1;
	}

	return numBytes;

}

int ofxFTPClient::get(string fileName, string localFolder, string remoteFolder)
{
	if( bSetup == false ){
		if( bVerbose )printf("error - you need to call setup first\n");
		return -1;
	}

	int numBytes = 0;

	try{
		startFtpSesssion();

		if( bVerbose )printf("ftp-ing %s\n", fileName.c_str());

		//localFolder = ofToDataPath( localFolder );

		//add slashes if they don't exist
		if(localFolder.length() > 0){
			if( localFolder[localFolder.length()-1] != '/' ){
				localFolder += "/";
			}
		}

		if(remoteFolder.length() > 0){
			if( remoteFolder[remoteFolder.length()-1] != '/' ){
				remoteFolder += "/";
			}
		}

		string localPath    = localFolder  + fileName;
		string remotePath   = remoteFolder + fileName;

		ostringstream remoteOSS;
		remoteOSS << remoteFolder << fileName;

		if( bVerbose )printf("localpath is %s\n remotepath is %s\n", localPath.c_str(), remotePath.c_str());

		ftpClient->setFileType(Poco::Net::FTPClientSession::TYPE_BINARY);
		istream& ftpOStream = ftpClient->beginDownload(remoteOSS.str().c_str());

		ofstream localIFStream(localPath.c_str(), ifstream::out | ifstream::binary);
		numBytes = Poco::StreamCopier::copyStream(ftpOStream, localIFStream);
		ftpClient->endDownload();
		endFtpSession();

		if(bVerbose)printf("downloaded %i bytes\n\n", numBytes);

		return numBytes;

	}
	catch ( Poco::Net::FTPException& e)
	{
		cout << e.displayText() << endl;
		return -1;
	}
	catch (Poco::Exception& exc)
	{
		cout << exc.displayText() << endl;
		return -1;
	}
}

vector<string> ofxFTPClient::list(string path)
{
    try{
        startFtpSesssion();
        string res;
        istream &ist = ftpClient->beginList(path, true);
        Poco::StreamCopier::copyToString(ist, res);
        ftpClient->endList();
        
        return ofSplitString(res, "\n", true, true);
        endFtpSession();
    }
    catch ( Poco::Net::FTPException& e)
    {
        cout << e.displayText() << endl;
        return vector<string>();
    }
	catch (Poco::Exception& exc)
	{
		cout << exc.displayText() << endl;
		return vector<string>();
	}

}
void ofxFTPClient::setVerbose(bool verbose){
    bVerbose = verbose;
}