#pragma once

#include "ofMain.h"

#include "Poco/Net/FTPClientSession.h"
#include "Poco/StreamCopier.h"
#include "Poco/Net/NetException.h"

class ofxFTPClient
{
public:
	ofxFTPClient();
	void setup(string _host, int _port = 21, string username = "anonymous", string password = "");

	int sendFromOf(string fileName, string localFolder/*data-path*/, string remoteFolder);
	int send(string fileName, string localFolder, string remoteFolder);
	int getToOf(string fileName, string localFolder/*data-path*/, string remoteFolder);
	int get(string fileName, string localFolder, string remoteFolder);

	vector<string> list(string path);
	void setPASV(bool p){pasv = p;}
	void setVerbose(bool verbose);

private:
	//------------------------------------------------------------
    void startFtpSesssion(){
        endFtpSession();		
        ftpClient = new Poco::Net::FTPClientSession(host, port);
		ftpClient->login(user, pass);
		ftpClient->setPassive(pasv);
    }
    
    //------------------------------------------------------------
    void endFtpSession(){
        if( ftpClient != NULL ){
            ftpClient->close();
            delete ftpClient;
            ftpClient = NULL;
        }
    }

	bool bVerbose;
    
    Poco::Net::FTPClientSession* ftpClient;
    string user, host, pass;
    int port;
    bool bSetup;
	bool pasv;

};