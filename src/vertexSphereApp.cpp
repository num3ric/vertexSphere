#include "cinder/app/AppBasic.h"
#include "cinder/Vector.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/ImageIo.h"
#include "cinder/Quaternion.h"

using namespace ci;
using namespace ci::app;

class vertexSphereApp : public AppBasic {
public:
	void prepareSettings( Settings *settings );
	void setup();
	void mouseMove(MouseEvent event);
	void update();
	void draw();
	
private:
	Vec2f mMouse;
	float mAngle;
	Vec3f mAxis;
	Quatf mQuat;
	gl::GlslProg mShader;
	gl::Texture		mTexture;	
};
void vertexSphereApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 800, 800 );
	//settings->setFullScreen( true );
}

void vertexSphereApp::setup()
{	
	mAngle = 0.0f;
	mAxis = Vec3f(0.0f, 1.0f, 0.0f);
	mQuat = Quatf( mAxis, mAngle );
	
	mShader = gl::GlslProg( loadResource( "mShader.vert" ), loadResource( "mShader.frag" ));
	mTexture = gl::Texture( loadImage( loadResource( "nebula.jpg" ) ) );
	mTexture.setWrap( GL_REPEAT, GL_REPEAT );
	mTexture.setMinFilter( GL_NEAREST );
	mTexture.setMagFilter( GL_NEAREST );
	gl::enableDepthRead();
}

void vertexSphereApp::mouseMove( MouseEvent event )
{
    mMouse = event.getPos();
}


void vertexSphereApp::update(){
	mAngle += 0.010f;	
	mQuat.set(mAxis, mAngle);
}

void vertexSphereApp::draw(){
	gl::clear();
	
	mTexture.enableAndBind();
	mShader.bind();
	mShader.uniform("normScale", (mMouse.x)/5.0f);
	mShader.uniform("colorMap", 0 );
	mShader.uniform("displacementMap", 0 );
	gl::pushModelView();
	gl::translate(Vec3f(0.5f*getWindowWidth(), 0.5f*getWindowHeight(),0));
	gl::rotate(mQuat);
	gl::drawSphere( Vec3f(0,0,0), 200,500);
	gl::popModelView();
	mShader.unbind();
	mTexture.unbind();
}

// This line tells Cinder to actually create the application
CINDER_APP_BASIC( vertexSphereApp, RendererGl )
