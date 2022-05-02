//#define DEBUG_SOCKET
#define DEBUG_IP "192.168.2.2"
#define DEBUG_PORT 9023

#include "ps4.h"

unsigned checksum(void *buffer, size_t len, unsigned int seed)
{
      unsigned char *buf = (unsigned char *)buffer;
      size_t i;

      for (i = 0; i < len; ++i)
            seed += (unsigned int)(*buf++);
      return seed;
}

int _main(struct thread *td) {
  UNUSED(td);

  initKernel();
  initLibc();

#ifdef DEBUG_SOCKET
  initNetwork();
  DEBUG_SOCK = SckConnect(DEBUG_IP, DEBUG_PORT);
#endif

  jailbreak();

  initSysUtil();

  //unlink("/data/update/PS4UPDATE.PUP");
  //rmdir("/data/update/");
  //mkdir("/data/update/", 777);
  //copy_file("/mnt/disc/PS4/UPDATE/PS4UPDATE.PUP", "/data/update/PS4UPDATE.PUP");

  FILE *fp;
  size_t len;
  char buf[4096], *file = "/mnt/disc/PS4/UPDATE/PS4UPDATE.PUP";

  if (NULL == (fp = fopen(file, "rb")))
  {
        printf_notification("Unable to open %s for reading\n", file);
        return -1;
  }
  len = fread(buf, sizeof(char), sizeof(buf), fp);
  printf_notification("%d bytes read\n", len);
  printf_notification("The checksum of %s is %d\n", file, checksum(buf, len, 0));

#ifdef DEBUG_SOCKET
  printf_debug("Closing socket...\n");
  SckClose(DEBUG_SOCK);
#endif

  return 0;
}
