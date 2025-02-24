#pragma once

#include"hittable.h"
#include<vector>
#include<memory>
#include<iostream>

namespace PT {
	class BVH_Node : public hittable {
	public:
		BVH_Node() = default;
		BVH_Node(const hittable_list& list, double time0, double time1);
		BVH_Node(
			const std::vector<std::shared_ptr<hittable>>& src_objects,
			size_t start, size_t end, double time0, double time1
		);

		virtual bool hit(const Ray& r, double t_min, double t_max, hitRecord& rec) const override;
		virtual bool bounding_box(double time0, double time1, AABB& output_box) const override;

	public:
		std::shared_ptr<hittable> left; // left child
		std::shared_ptr<hittable> right; // right child
		AABB box;
	};
	inline bool box_compare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b, int axis);

	bool box_x_compare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b);

	bool box_y_compare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b);

	bool box_z_compare(const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b); 
}
