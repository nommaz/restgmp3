// This file generated by ngrestcg
// For more information, please visit: https://github.com/loentar/ngrest

#ifndef WS_VFXBRIDGER_H
#define WS_VFXBRIDGER_H

#include <ngrest/common/Service.h> 
#include <ngrest/common/HttpException.h>

#include <PrinterLib/HuginPrinter.h>
#include <PrinterLib/Utilities.h>
#include <PrinterLib/Logger.h>
  
class HP  
{
public:
	static HuginPrinter* inst()
	{ 
		static HuginPrinter* instance = NULL;
		 

		if (instance == NULL)
		{
			instance = new HuginPrinter();  
		}
		return instance;
	}

	static bool lock(int fLock = -1)
	{
		static bool s_fLock = false;

		if (fLock == -1) return s_fLock; 

		s_fLock = ((fLock == 0) ? false: true); 

		return s_fLock;
	}
};



//! Dummy description for the service
/*! Some detailed description of the service */
// '*location' comment sets resource path for this service
// *location: ws_vfxbridger
class ws_vfxbridger: public ngrest::Service
{
	 
public:  
    // Here is an example of service operation
    //! Dummy description for the operation
    /*! Some detailed description of the operation */
    // To invoke this operation from browser open: http://localhost:9098/ws_vfxbridger/World! 
    //
    // '*location' metacomment sets path to operation relative to service operation.
    // Default value is operation name.
    // This will bind "echo" method to resource path: http://host:port/ws_vfxbridger/{text}
    // *location: /{text}
    //
    // '*method' metacomment sets HTTP method for the operation. GET is default method.
    // *method: GET
    // 
    
	std::string echo(const std::string& text)
    {
		std::string rv;

		//NGREST_ASSERT_HTTP(!HP::lock(), ngrest::HTTP_STATUS_423_LOCKED, "Service busy");

		//HP::lock(1);

		Logger::SetLogLevel(Logger::HIDE_BUG);

		if (text == "9")
		{ 
			rv = HP::inst()->SerialConnect("/dev/ttyACM0", 115200) ? "1" : "0";
		}
		  
		else if (text == "0")
		{ 
			DevInfo di;
			di.IP = "127.0.0.1";
			di.TerminalNo = "FO00007005";
			di.Brand = "HUGIN";
			di.Model = "HUGIN COMPACT";
			di.Version = "1.0.4";
			di.SerialNum  = "12345678"; 

			rv = HP::inst()->Connect(di, di.TerminalNo, "") ? "1" : "0";
		}
		else if (text == "1")
		{
			rv = HP::inst()->CheckPrinterStatus();
		}
		else if (text == "2")
		{
			rv = HP::inst()->PrintDocumentHeader();
		}
		else if (text == "3")
		{ 
			rv = HP::inst()->PrintItem(1, 15, 3.00, ToVector("SAMPLE PRODUCT"), ToVector(""), 1, 1);
		}
		else if (text == "4")
		{
			rv = HP::inst()->PrintPayment(0, -1, 45.0);
		}
		else if (text == "5")
		{
			rv = HP::inst()->CloseReceipt(false);
		}

		HP::lock(0);

		
        return text + " " + rv;// " b1(" + b1 + ") b2(" + b2 + ")";
    }


};


#endif // WS_VFXBRIDGER_H



