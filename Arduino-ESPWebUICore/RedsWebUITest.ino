#include "GlobalVariables.h"
#include "Initialization.h"

void setup()
{
  Initialization();
}

void loop()
{
  WebServer.handleClient();
  ftpSrv.handleFTP();
  delay(100);
}