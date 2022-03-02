#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
	public:
		bool IsEnabled();
		void Enabled(bool enabled);

		virtual void Update() = 0;

	private:
		bool _enabled;
};

#endif 

