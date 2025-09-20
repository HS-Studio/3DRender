import bpy
import os

def float_to_rgb565(r, g, b):
    """Konvertiert 0..1 floats zu RGB565 (16-bit)."""
    r5 = int(round(r * 31)) & 0x1F
    g6 = int(round(g * 63)) & 0x3F
    b5 = int(round(b * 31)) & 0x1F
    return (r5 << 11) | (g6 << 5) | b5

def get_material_rgb565(material):
    """Extrahiert Base Color → RGB565. Fallback: Weiß."""
    if not material:
        return 0xFFFF, "None"
    if material.node_tree:
        bsdf = material.node_tree.nodes.get("Principled BSDF")
        if bsdf and "Base Color" in bsdf.inputs:
            col = bsdf.inputs["Base Color"].default_value
            return float_to_rgb565(col[0], col[1], col[2]), material.name
    # Fallback: diffuse_color
    col = material.diffuse_color
    return float_to_rgb565(col[0], col[1], col[2]), material.name

def export_object_to_h(obj, output_path):
    if obj.type != 'MESH':
        print("Ausgewähltes Objekt ist kein Mesh!")
        return

    mesh = obj.data
    mesh.calc_loop_triangles()
    #mesh.calc_normals_split()

    verts = [v.co for v in mesh.vertices]
    edges = [e.vertices for e in mesh.edges]
    faces = [p.vertices for p in mesh.polygons]
    normals = [p.normal for p in mesh.polygons]
    face_material_ids = [p.material_index for p in mesh.polygons]

    # Materialfarben als RGB565 + Namen
    mat_slots = obj.material_slots
    mat_colors = [get_material_rgb565(slot.material) for slot in mat_slots]

    name = obj.name.replace(" ", "_")

    with open(output_path, 'w') as f:
        f.write("// {}\n\n".format(output_path.split(os.sep)[-1]))
        f.write("#ifndef TMODEL_DEFINED\n")
        f.write("#define TMODEL_DEFINED\n\n")
        f.write("typedef struct\n{\n")
        f.write("  const float (*verts)[3];\n")
        f.write("  const uint16_t (*edges)[2];\n")
        f.write("  const uint16_t (*faces)[4];\n")
        f.write("  const float (*normals)[3];\n")
        f.write("  const uint16_t *colors;\n")
        f.write("  const uint8_t *faceColorIDs;\n")
        f.write("  uint16_t numVerts;\n")
        f.write("  uint16_t numEdges;\n")
        f.write("  uint16_t numFaces;\n")
        f.write("} tModel;\n\n")
        f.write("#endif\n\n")
        f.write("#include <stdint.h>\n")
    
        # Verts
        f.write(f"// {name} Verts\n")
        f.write(f"static const float {name}Verts[{len(verts)}][3] = {{\n")
        for v in verts:
            f.write(f"    {{ {v.x:.6f}, {v.y:.6f}, {v.z:.6f} }},\n")
        f.write("};\n\n")

        # Edges
        f.write(f"// {name} Edges\n")
        f.write(f"const uint16_t {name}Edges[{len(edges)}][2] = {{\n")
        for e in edges:
            f.write(f"    {{{e[0]}, {e[1]}}},\n")
        f.write("};\n\n")

        # Faces
        f.write(f"// {name} Faces\n")
        f.write(f"const uint16_t {name}Faces[{len(faces)}][4] = {{\n")
        for f_idx in faces:
            if len(f_idx) == 4:
                f.write(f"    {{{f_idx[0]}, {f_idx[1]}, {f_idx[2]}, {f_idx[3]}}},\n")
            elif len(f_idx) == 3:
                f.write(f"    {{{f_idx[0]}, {f_idx[1]}, {f_idx[2]}, {f_idx[2]}}},\n")
        f.write("};\n\n")

        # Normals
        f.write(f"// {name} Normals\n")
        f.write(f"const float {name}Normals[{len(normals)}][3] = {{\n")
        for n in normals:
            f.write(f"    {{ {n.x:.6f}, {n.y:.6f}, {n.z:.6f} }},\n")
        f.write("};\n\n")

        # Colors (RGB565 mit Kommentar)
        f.write("// Farben für jede Material-Slot (RGB565 aus BaseColor)\n")
        f.write(f"const uint16_t {name}Colors[{len(mat_colors)}] = {{\n")
        for c, mat_name in mat_colors:
            f.write(f"    0x{c:04X}, // {mat_name}\n")
        f.write("};\n\n")

        # FaceColorIDs
        f.write(f"// {name} Face Material IDs\n")
        f.write(f"const uint8_t {name}FaceColors[{len(face_material_ids)}] = {{\n")
        for mat_id in face_material_ids:
            f.write(f"    {mat_id},\n")
        f.write("};\n\n")

        # tModel Instanz
        f.write(f"const tModel m_{name} = {{\n")
        f.write(f"    {name}Verts,\n")
        f.write(f"    {name}Edges,\n")
        f.write(f"    {name}Faces,\n")
        f.write(f"    {name}Normals,\n")
        f.write(f"    {name}Colors,\n")
        f.write(f"    {name}FaceColors,\n")
        f.write(f"    {len(verts)}, {len(edges)}, {len(faces)}\n")
        f.write("};\n\n")
        f.write("// EOF\n")

    print(f"{output_path} erfolgreich erstellt!")

# Beispielaufruf
obj = bpy.context.active_object
output_path = os.path.join(bpy.path.abspath("//"), f"{obj.name}.h")
export_object_to_h(obj, output_path)
