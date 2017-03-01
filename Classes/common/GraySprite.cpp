#include "GraySprite.h"

#include "cocos2d.h"
USING_NS_CC;

// 构造函数
GraySprite::GraySprite()
{
}


// 析构函数
GraySprite::~GraySprite()
{

}


// 生成一个灰度精灵
GraySprite* GraySprite::create( cocos2d::Texture2D* pTexture, const cocos2d::Rect& tRect )
{
	GraySprite* pSprGrayScale = new GraySprite;
	if (pSprGrayScale && pSprGrayScale->initWithTexture(pTexture,tRect))
	{
		pSprGrayScale->autorelease();
	}
	else
	{
		CC_SAFE_RELEASE(pSprGrayScale);
	}
	return pSprGrayScale;
}

// 生成一个灰度精灵
GraySprite* GraySprite::create( const char* pszFileName )
{
	GraySprite* pSprGrayScale = new GraySprite;
	if (pSprGrayScale && pSprGrayScale->initWithFile(pszFileName))
	{
		pSprGrayScale->autorelease();
	}
	else
	{
		CC_SAFE_RELEASE(pSprGrayScale);
	}
	return pSprGrayScale;
}
GraySprite* GraySprite::create( std::string spriteName,int png)
{
	std::string file=spriteName+".png";
	GraySprite* pSprGrayScale = new GraySprite;
	if (pSprGrayScale && pSprGrayScale->initWithFile(file.c_str()))
	{
		pSprGrayScale->setAnchorPoint(Point::ANCHOR_MIDDLE);
		pSprGrayScale->autorelease();
	}
	else
	{
		CC_SAFE_RELEASE(pSprGrayScale);
	}
	return pSprGrayScale;
}

// 初始化灰度精灵
bool GraySprite::initWithTexture( cocos2d::Texture2D* pTexture, const cocos2d::Rect& tRect )
{
	do 
	{
//		CC_BREAK_IF(!CCSprite::initWithTexture(pTexture, tRect));
//
//		GLchar* pszFragSource ="#ifdef GL_ES \n \
//			precision mediump float; \n \
//			#endif \n \
//			uniform sampler2D u_texture; \n \
//			varying vec2 v_texCoord; \n \
//			varying vec4 v_fragmentColor; \n \
//			void main(void) \n \
//			{ \n \
//			// Convert to greyscale using NTSC weightings \n \
//			vec4 col = texture2D(u_texture, v_texCoord); \n \
//			float grey = dot(col.rgb, vec3(0.299, 0.587, 0.114)); \n \
//			gl_FragColor = vec4(grey, grey, grey, col.a); \n \
//			}";  
//		CCGLProgram* pProgram = new CCGLProgram();
//		pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, pszFragSource);
//		this->setShaderProgram(pProgram);
//		pProgram->release();
//		CHECK_GL_ERROR_DEBUG();
//
//		this->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
//		this->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
//		this->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
//		CHECK_GL_ERROR_DEBUG();
//
//		this->getShaderProgram()->link();
//		CHECK_GL_ERROR_DEBUG();
//
//		this->getShaderProgram()->updateUniforms();
//		CHECK_GL_ERROR_DEBUG();

		return true;
	} while (0);
	return false;
}


// 绘图事件
//void GraySprite::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
//{
//	// Don't do calculate the culling if the transform was not updated
//	_insideBounds = transformUpdated ? isInsideBounds() : _insideBounds;
//
//	if(_insideBounds)
//	{
//		_quadCommand.init(_globalZOrder, _texture->getName(), _shaderProgram, _blendFunc, &_quad, 1, transform);
//		renderer->addCommand(&_quadCommand);
//	}
//	//Sprite::draw(renderer, transform, transformUpdated);
//}