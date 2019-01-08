#pragma once

#define SAFE_DELETE(p) if(p) { delete p; p = NULL;}
#define SAFE_DELETE_ARRAY(p) if(p) { delete[] p; p = NULL;}
#define SAFE_RELEASE(p) if(p) { p->Release(); p = NULL; }
#define DECLARE_SINGLE(Type) \
	private:\
		static Type* m_pInstance;\
	public:\
		static Type* GetInstance()\
		{\
			if(!m_pInstance)\
				m_pInstance = new Type;\
			return m_pInstance;\
		}\
		static void DestroyInstance()\
		{\
			SAFE_DELETE(m_pInstance);\
		}\
	private:\
		Type();\
	   ~Type();
#define DEFINITION_SINGLE(Type) Type* Type::m_pInstance = NULL;
#define GET_SINGLE(Type)		Type::GetInstance()
#define DESTROY_SINGLE(Type)	Type::DestroyInstance()