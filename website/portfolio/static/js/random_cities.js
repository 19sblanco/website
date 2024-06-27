/*
given an integer n, return n city objects
where each city coordinate is random
*/
function get_random_cities(n) {
    min = Math.ceil(0);
    max = Math.floor(100);
    let points = [];
    for (let i = 0; i < n; i++) {
        x = Math.floor(Math.random() * (max - min + 1)) + min;
        y = Math.floor(Math.random() * (max - min + 1)) + min;
        let point = { x: x, y: y }; 
        points.push(point);
    }
    console.log();
    console.log(points);
    console.log();
    return points;
}