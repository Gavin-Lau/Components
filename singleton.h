/******************************************************************************
*
*									JAS V1.0
*
*           Copyright (C) 2015-2018, ���ڽ�㴴����Ϣ�������޹�˾
*
*                             All Rights Reserved.
*
* ===========================================================================
*
* �� �� ����singleton.h
* ģ�����ƣ�singleton��������
* ����˵����singleton��������������
* ��    �ߣ�
* �������ڣ�2015-10-12
* �� �� �ţ�1.0
* �޸���ʷ��
*
* �޸�����       ����            ����
* ---------------------------------------------------------------------------
* 2015-10-12     liulj         ��ʼ�汾
*
******************************************************************************/

#if !defined(__SINGLETON_INCLUDE_H)
#define __SINGLETON_INCLUDE_H

#include "critical_section.h"

template <class object>
class singleton
{
protected:
	singleton();
	virtual ~singleton();
public:
	static object*          instance();
	static void             release();
protected:
	static void             init();
private:
	static  object      *   jas_instance;
	static  unsigned int    jas_count;
	static critical_section cs;
};

template <class object>
object  *   singleton<object>::jas_instance = 0;

template <class object>
unsigned int    singleton<object>::jas_count = 0;

template <class object>
critical_section   singleton<object>::cs;

template <class object>
singleton<object>::singleton()
{
}

template <class object>
singleton<object>::~singleton()
{
}

template <class object>
object*  singleton<object>::instance()
{
	init();
	return (jas_instance);
}

template <class object>
void singleton<object>::release()
{
	if (jas_instance != 0)
	{
		critical_function lock(cs);
		if (jas_instance != 0)
		{
			delete jas_instance;
			jas_instance = 0;
		}
	}
}

template <class object>
void singleton<object>::init()
{
	if (jas_instance == 0)
	{
		critical_function lock(cs);
		if (jas_instance == 0)
		{
			jas_instance = new object;
		}
	}
}

#endif // !defined(__SINGLETON_INCLUDE_H)