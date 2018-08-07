#![feature(plugin, custom_attribute)]

extern crate rand;
extern crate time;

use time::PreciseTime;
extern crate flame;
use std::fs::File;
mod knn;

use knn::compute_centroids;
use knn::Point;

fn generate_point() -> Point {
	return Point{
		w: rand::random::<f32>(),
		x: rand::random::<f32>(),
		y: rand::random::<f32>(),
		z: rand::random::<f32>(),
		centroid: -1
	}
}

fn main() {
	let mut points = [Point{w:0.0,x:0.0, y:0.0,z:0.0, centroid:-1}; 50000];
	for i in 0..50000 {
		points[i] = generate_point();
	}
	flame::start("compute centroids");
	compute_centroids(&mut points);
    flame::end("compute centroids");
	let start = PreciseTime::now();
	// whatever you want to do
	let end = PreciseTime::now();
	flame::dump_html(&mut File::create("flame-graph.html").unwrap()).unwrap();

}

