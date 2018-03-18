#pragma once
namespace Sim {
	class GameInstance
	{
	public:
		GameInstance();
		virtual ~GameInstance();
		virtual void Update();
	};
}

