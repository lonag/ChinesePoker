#ifndef __GRAY_SPRITE_H__
#define __GRAY_SPRITE_H__

#include "cocos2d.h"
USING_NS_CC;
class GraySprite : public cocos2d::Sprite
{
public:

	/** 
	 * @brief ���캯��
	 */
	GraySprite();


	/** 
	 * @brief ��������
	 */
	virtual ~GraySprite();


	/**
	 * @brief ����һ���ҶȾ��� 
	 * @param [in] pszFileName ͼƬ�ļ���
	 * @retval ���ɳɹ�������һ���ҶȾ������ָ��
	 * @retval ����ʧ�ܣ����� 0
	 */
	static GraySprite* create(const char* pszFileName);
	static GraySprite* create(std::string spriteName,int png);
	static GraySprite* create( cocos2d::Texture2D* pTexture, const cocos2d::Rect& tRect );

	/** 
	 * @brief ��ʼ���ҶȾ���
	 * @param [in] pTexture �������
	 * @param [in] tRect ����ü�����
	 * @retval ��ʼ���ɹ�������true
	 * @retval ��ʼ��ʧ�ܣ�����false
	 */
	bool initWithTexture(cocos2d::Texture2D* pTexture, const cocos2d::Rect&  tRect);


	/** 
	 * @brief ��ͼ�¼�
	 */
	 //virtual void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;

};

#endif // __MM_GRAY_SCALE_SPRITE_H__