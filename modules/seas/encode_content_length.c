/* $Id$
 *
 * Copyright (C) 2006-2007 VozTelecom Sistemas S.L
 *
 * This file is part of opensips, a free SIP server.
 *
 * opensips is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * opensips is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * =====================================================================================
 *
 *        Filename:  encode_content_length.c
 *
 *     Description:  Function to encode content-length headers.
 *
 *         Version:  1.0
 *         Created:  21/11/05 02:02:58 CET
 *        Revision:  none
 *        Compiler:  gcc
 *
 *          Author:  Elias Baixas (EB), elias@conillera.net
 *         Company:  VozTele.com
 *
 * =====================================================================================
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>

/*
 * Encodes a content-length header.
 * encoding is as follows:
 * 1: length of the payload.
 * N: Network-Byte-Ordered(little endian) of the
 * multibyte number represeting the length (now, it is
 * a long integer)
 */
int encode_contentlength(char *hdr,int hdrlen,long int len,char *where)
{
   long int longint;

   longint = htonl(len);
   where[0]=sizeof(long int);
   memcpy(&where[1],&longint,sizeof(long int));
   return 1+sizeof(long int);

}

int print_encoded_contentlength(FILE *fp,char *hdr,int hdrlen,unsigned char *payload,int paylen,char *prefix)
{
   long int content_length;
   int i;

   memcpy(&content_length,&payload[1],payload[0]);
   content_length=ntohl(content_length);

   fprintf(fp,"%s",prefix);
   for(i=0;i<paylen;i++)
      fprintf(fp,"%s%d%s",i==0?"ENCODED CONTENT LENGTH BODY:[":":",payload[i],i==paylen-1?"]\n":"");
   fprintf(fp,"%s  CONTENT LENGTH=[%d]\n",prefix,(int)content_length);
   return 1;
}

