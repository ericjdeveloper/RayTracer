import math as m
import random as r

def generate_voronoi_ppm(fname, size):
    def dist(a):
        return m.sqrt(a[0] ** 2 + a[1] ** 2)
    vertices = [(r.randint(0, size), r.randint(0,size)) for i in range(10)]

    print(fname, size)
    with open(fname, "w") as outfile:
        outfile.write("P3\n")
        outfile.write(f"{size} {size}\n")
        outfile.write("255\n")


        for i in range(size):
            for j in range(size):
                vertices.sort(key=lambda v: dist((i - v[0], j - v[1])))
                closest = vertices[0]
                closest_second = vertices[1]

                d_1 = dist((i - closest[0], j - closest[1]))
                d_2 = dist((i - closest_second[0], j - closest_second[1]))
                brightness =  (d_2 - d_1) / d_2

                val = int(brightness * 255)
                outfile.write(f"{val} {val} {val} ")
            outfile.write("\n")
        

if __name__ == "__main__":
    import sys
    generate_voronoi_ppm(sys.argv[1], int(sys.argv[2]))