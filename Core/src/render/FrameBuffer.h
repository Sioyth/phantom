#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

namespace Phantom 
{
	class FrameBuffer
	{
		public:
			void Bind();
			void Unbind();
			inline const unsigned int& ID() { return _id; };
			inline const unsigned int& Texture() { return _texture; };
			inline const unsigned int& Witdh() { return _width; };
			inline const unsigned int& Height() { return _height; };
			void Resize(const unsigned int& width, const unsigned int& heigth);
			bool Create(const unsigned int& width, const unsigned int& heigth);

			void Delete();
			~FrameBuffer();

		private:
			unsigned int _id;
			unsigned int _width;
			unsigned int _height;
			unsigned int _texture;
	};
}
#endif;

