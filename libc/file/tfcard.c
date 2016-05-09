/***********************************************************************
*   Copyright (C) 2016 pilot-lab.inc All rights reserved.
*   
*   @file:       tfcard.c
*   @brief:      
*   @author:     Pilot labs
*   @maintainer: frank.fu@pilot-lab.com.cn
*   @version:    1.0
*   @date:       2016-05-09
*   
***********************************************************************/
#include "file.h"
#include "log.h"
#include <stdio.h>
#include <sys/vfs.h>
#include <errno.h>


#define TFCARDPATH "/mnt/mmcblk0"

#ifndef PL_TAG
#define PL_TAG "TFCARD"
#endif

#define KBYTES (1 << 10)
#define MBYTES (1 << 20)
#define GBYTES (1 << 30)

#define KB(X) ((X) >> 10)
#define MB(X) ((X) >> 20)
#define GB(X) ((X) >> 30)

typedef enum
{
	e_B = 0x01,
	e_K,
	e_M,
	e_G,
}SIZETYPE_E;

typedef struct _size_S
{
	float 		m_fSize;
	SIZETYPE_E 	m_eSizeType;
}SIZE_S;



int tfcard_is_exist(const char* pcPath)
{
	if (NULL == pcPath) 
	{
		PL_LOGE(PL_TAG, "NULL == pcPath\n");
		return -1;
	}

    return	(!file_is_exist(pcPath));
}


int getUsedSize(const char* pcPath, SIZE_S* psSize)
{
	if (-1 == tfcard_is_exist(pcPath))
	{
		PL_LOGE(PL_TAG, "%s is not exist\n", pcPath);
		return -1.0;
	}

	struct statfs disk_info;

	if (statfs(pcPath, &disk_info) == -1)
    {
		PL_LOGE(PL_TAG, "failed to get %s infomation,errno:%u, reason:%s\n",pcPath, errno, strerror(errno));
		return -1.0;
	}

	unsigned long used_size = (disk_info.f_blocks - disk_info.f_bavail);

	if (used_size > ())
}

int getTotalSize(const char* pcPath, SIZE_S* psSize)
{
	if (-1 == tfcard_is_exist(pcPath))
	{
		PL_LOGE(PL_TAG, "%s is not exist\n", pcPath);
		return -1;
	}

	struct statfs disk_info;

	if (statfs(pcPath, &disk_info) == -1)
    {
		PL_LOGE(PL_TAG, "failed to get %s infomation,errno:%u, reason:%s\n",pcPath, errno, strerror(errno));
		return -1;
	}

	unsigned int uTotalSize = (KB(disk_info.f_blocks)) * (KB(disk_info.f_bsize));
	if (uTotalSize >= 1024)
	{
		psSize->m_fSize = (uTotalSize/1000.0);
		psSize->m_eSizeType = e_G;
	}
	else
	{
		psSize->m_fSize = (float)uTotalSize;
		psSize->m_eSizeType = e_M;
	}

	return 0;
}

int getAvailableSize(const char* pcPath, SIZE_S* psSize)
{
	if (-1 == tfcard_is_exist(pcPath))
	{
		PL_LOGE(PL_TAG, "%s is not exist\n", pcPath);
		return -1;
	}

	struct statfs disk_info;

	if (statfs(pcPath, &disk_info) == -1)
    {
		PL_LOGE(PL_TAG, "failed to get %s infomation,errno:%u, reason:%s\n",pcPath, errno, strerror(errno));
		return -1;
	}

	unsigned long available_size = (disk_info.f_bavail >> 10)* (disk_info.f_bsize >> 10);
	if (available_size >= 1024)
	{
		psSize->m_fSize = (available_size/1000.0);
		psSize->m_eSizeType = e_G;
	}
	else
	{
		psSize->m_fSize = (float)available_size;
		psSize->m_eSizeType = e_M;
	}

	return 0;
}

int main(int argc, char** argv)
{
	printf("KBYTES =%lu", KBYTES);
	printf("MBYTES =%lu", MBYTES);
	printf("GBYTES =%lu", GBYTES);

	if (-1 == tfcard_is_exist(TFCARDPATH))
	{
		PL_LOGE(PL_TAG, "%s is not exist\n", TFCARDPATH);
		return -1;
	}

	struct statfs disk_info;

	if (statfs(TFCARDPATH, &disk_info) == -1)
    {
		PL_LOGE(PL_TAG, "Failed to get file disk infomation,errno:%u, reason:%s\n", errno, strerror(errno));
		return -1;
	}
		
	unsigned long total_size = (disk_info.f_blocks>>10) * (disk_info.f_bsize>>10);
	unsigned long available_size = (disk_info.f_bavail >> 10)* (disk_info.f_bsize >> 10);
	unsigned long free_size = (disk_info.f_bfree >> 10)* (disk_info.f_bsize >> 10);
	unsigned long used_size = (disk_info.f_blocks - disk_info.f_bavail)
	printf("disk_info.f_bsize >> 10=%lu\n",disk_info.f_bsize >> 10);
	printf("disk_info.f_bavail >> 10=%lu\n",disk_info.f_bavail >> 10 );
	printf("disk_info.f_bfree >> 20=%lu\n",disk_info.f_bfree >> 20);

	//���ÿ����ĳ��ȣ�linux���ڴ��Ϊ4KB
	printf("block size: %ld bytes\n", disk_info.f_bsize);
	//��������
	printf("total data blocks: %ld \n", disk_info.f_blocks);
	//���path���ڴ��̵Ĵ�С
	printf("total file disk size: %ld MB\n",total_size);
	//�����root�û������õĴ��̿ռ��С
	printf("avaiable size: %ld MB\n",available_size);
	//���Ӳ�̵�����ʣ��ռ�
	printf("free size: %ld MB\n",free_size);
	//����������ļ��ڵ����
	printf("total file nodes: %ld\n", disk_info.f_files);
	//��������ļ��ڵ����
	printf("free file nodes: %ld\n", disk_info.f_ffree);
	//����ļ�����󳤶�
	printf("maxinum length of file name: %ld\n", disk_info.f_namelen);

	return 0;

}