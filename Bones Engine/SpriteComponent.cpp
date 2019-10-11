#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner),
	 texture(nullptr),
	 drawOrder(drawOrder),
	 texWidth(0),
	 texHeight(0) {
	this->owner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
	owner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader) {
	if (texture)
	{
		// Scale the quad by the width/height of texture
		Eigen::Matrix4f scaleMat;
		scaleMat = Math::CreateScale4f(texWidth, texHeight, 1.0f);

		Eigen::Matrix4f world = scaleMat * owner->GetWorldTransform();

		// Set shaders and verts active before drawing sprites

		// World transform
		shader->SetMatrixUniform("uWorldTransform", world);
		texture->SetActive();
		// Draw quad
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

void SpriteComponent::SetTexture(Texture* texture) {
	texture = texture;
	texWidth = texture->GetWidth();
	texHeight = texture->GetHeight();
}
