def convert_to_triangles(input_file, output_file):
    with open(input_file, 'r') as f_in, open(output_file, 'w') as f_out:
        for line in f_in:
            if line.startswith('f '):
                vertices = line.strip().split()[1:]
                if len(vertices) == 3:  # Triangle
                    v0, v1, v2 = vertices
                    f_out.write(f"f {v0.split('/')[0]} {v1.split('/')[0]} {v2.split('/')[0]}\n")
                elif len(vertices) == 4:  # Quad
                    v0, v1, v2, v3 = vertices
                    f_out.write(f"f {v0.split('/')[0]} {v1.split('/')[0]} {v2.split('/')[0]}\n")
                    f_out.write(f"f {v0.split('/')[0]} {v2.split('/')[0]} {v3.split('/')[0]}\n")
            elif line.startswith('v '):
                f_out.write(line)


convert_to_triangles("./models/sphere_cube.obj", "./build/sphere_cube.obj")