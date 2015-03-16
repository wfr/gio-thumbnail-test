/* Find the thumbnail for a file using GIO
 * (c) 2015 Wolfgang Frisch <wfr@roembden.net>
 * 
 * https://developer.gnome.org/gio/stable/GFile.html#g-file-query-info
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <string.h>

#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>

int
main(int argc, char **argv)
{
  GError *error = NULL;
  GFile *file = NULL;
  GFileInfo* info = NULL;

  if (argc != 2)
    {
      printf("usage: %s filename\n", argv[0]);
      return 1;
    }
  
  file = g_file_new_for_path(argv[1]);
  info = g_file_query_info(file,
                    G_FILE_ATTRIBUTE_THUMBNAIL_PATH ","
                    G_FILE_ATTRIBUTE_THUMBNAILING_FAILED ","
                    G_FILE_ATTRIBUTE_STANDARD_ICON,
                    G_FILE_QUERY_INFO_NONE,
                    NULL,
                    &error);
  if (error)
    {
      printf("g_file_query_info failed with code=%d\n", error->code);
      return 1;
    }
  else
    {
      const char *thumbnail_path = g_file_info_get_attribute_as_string(info,
                                     G_FILE_ATTRIBUTE_THUMBNAIL_PATH);
      printf("%s\n", thumbnail_path);
    }

  return 0;
}



/* vim:set expandtab cindent
 * cinoptions=>4,n-2,{2,^-2,:2,=2,g0,h2,p5,t0,+2,(0,u0,w1,m1 shiftwidth=2
 * softtabstop=2 textwidth=79 fo-=ro fo+=cql tabstop=2 : */
