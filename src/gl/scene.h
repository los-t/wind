/***************************************************************************
 * Project: wind
 * File: gl/scene.h
 * Author: Vladimir 'dvn' Dranyonkov <los-t@ya.ru>
 * Description: A 3d scene representation
 ***************************************************************************/

#ifndef WIND_GL_SCENE_H_
#define WIND_GL_SCENE_H_

#include <vector>

#include "gl/model.h"

namespace gl {

	class Scene {
		public:
			Scene() { }
			virtual ~Scene() {}

			void push(const Model& m) { models_.emplace_back(m); }

			std::vector<Model> visible_objects() const { return models_; }

		private:
			std::vector<Model> models_;
	};

} //namespace gl

#endif //WIND_GL_SCENE_H_
