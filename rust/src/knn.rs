extern crate flame;

#[derive(Copy, Clone)]
pub struct Point {
	pub w: f32,
	pub x: f32,
	pub y: f32,
	pub z: f32,
	pub centroid: i32
}

pub struct Centroid {
    pub w: f32,
    pub x: f32,
    pub y: f32,
    pub z: f32,
    pub index: i32
}


fn get_distance(p: &Point, c: &Centroid) -> f32 {
	let dw = (p.w - c.w) * (p.w - c.w);
	let dx = (p.x - c.x) * (p.x - c.x);
	let dy = (p.y - c.y) * (p.y - c.y);
	let dz = (p.z - c.z) * (p.z - c.z);
	return (dw + dx + dy + dz).sqrt();
}


fn closest_centroid(c: &[Centroid], p: &Point) -> i32 {
	let mut distance : f32= 3402823000000.0; 
	let mut index : i32 = -1;
	for i in 0..6 {
		let dist: f32 = get_distance(p, &c[i]);
		if dist < distance {
			index = i as i32;
			distance = dist;
		}
	}
	return index;
}


pub fn perform_iteration(centroids: &mut [Centroid], points: &mut [Point]){
    /*
     * Assign points to the closest centroids
     */
    for i in 0..50000 {
    	points[i].centroid = closest_centroid(centroids, &points[i]);
    }

    let mut centroid_count: [i32; 6] = [0;6];
    let mut centroid_values: [[ f32; 4]; 6] = [[0.0; 4]; 6];


    for j in 0..50000 {
    	let ctr = points[j].centroid as usize;
    	centroid_count[ctr] += 1;
    	centroid_values[ctr][0] = points[j].w;
        centroid_values[ctr][1] = points[j].x;
        centroid_values[ctr][2] = points[j].y;
        centroid_values[ctr][3] = points[j].z;
    }

    for k in 0..6 {
    	let count : f32 = centroid_count[k] as f32;
    	centroids[k].w = centroid_values[k][0] / count;
        centroids[k].x = centroid_values[k][1] / count;
        centroids[k].y = centroid_values[k][2] / count;
        centroids[k].z = centroid_values[k][3] / count;
    }
}


pub fn compute_centroids(points: &mut [Point]) {

	let mut centroids: [Centroid; 6] = [Centroid { w: points[0].w, x: points[0].x, y: points[0].y, z: points[0].z, index: 0 as i32},
	Centroid { w: points[1].w, x: points[1].x, y: points[1].y, z: points[1].z, index: 1 as i32},
	Centroid { w: points[2].w, x: points[2].x, y: points[2].y, z: points[2].z, index: 2 as i32},
	Centroid { w: points[3].w, x: points[3].x, y: points[3].y, z: points[3].z, index: 3 as i32},
	Centroid { w: points[4].w, x: points[4].x, y: points[4].y, z: points[4].z, index: 4 as i32},
	Centroid { w: points[5].w, x: points[5].x, y: points[5].y, z: points[5].z, index: 5 as i32}];

	for k in 0..50000 {
		points[k].centroid = (k as i32) % 6;
	}

	for _l in 0..1000 {
		flame::span_of("perform_iteration", || perform_iteration(&mut centroids, points));
	}
}
