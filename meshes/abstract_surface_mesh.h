/*********************************************************************************
*  Copyright(C) 2016: Marco Livesu                                               *
*  All rights reserved.                                                          *
*                                                                                *
*  This file is part of CinoLib                                                  *
*                                                                                *
*  CinoLib is dual-licensed:                                                     *
*                                                                                *
*   - For non-commercial use you can redistribute it and/or modify it under the  *
*     terms of the GNU General Public License as published by the Free Software  *
*     Foundation; either version 3 of the License, or (at your option) any later *
*     version.                                                                   *
*                                                                                *
*   - If you wish to use it as part of a commercial software, a proper agreement *
*     with the Author(s) must be reached, based on a proper licensing contract.  *
*                                                                                *
*  This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE       *
*  WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.     *
*                                                                                *
*  Author(s):                                                                    *
*                                                                                *
*     Marco Livesu (marco.livesu@gmail.com)                                      *
*     http://pers.ge.imati.cnr.it/livesu/                                        *
*                                                                                *
*     Italian National Research Council (CNR)                                    *
*     Institute for Applied Mathematics and Information Technologies (IMATI)     *
*     Via de Marini, 6                                                           *
*     16149 Genoa,                                                               *
*     Italy                                                                      *
**********************************************************************************/
#ifndef CINO_ABSTRACT_SURFACE_MESH_H
#define CINO_ABSTRACT_SURFACE_MESH_H

#include <cinolib/meshes/abstract_mesh.h>

namespace cinolib
{

template<class M,
         class V,
         class E,
         class F>
class AbstractSurfaceMesh : public AbstractMesh<M,V,E,F>
{
    public:

        void load(const char * filename);
        void save(const char * filename) const;

        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        void update_adjacency();

        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        uint verts_per_face(const uint fid) const { return this->faces.at(fid).size(); }
        uint verts_per_elem(const uint fid) const { return this->faces.at(fid).size(); }

        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        uint num_elems() const { return this->faces.size(); } // elem == face!!

        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        const std::vector<uint> & adj_elem2elem(const uint fid) const { return this->f2f.at(fid); }

        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        const F & elem_data(const uint fid) const { return this->f_data.at(fid); } // elem == face!!
              F & elem_data(const uint fid)       { return this->f_data.at(fid); }

        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        void               normalize_area();
        std::vector<uint>  get_boundary_vertices() const;
        std::vector<ipair> get_boundary_edges() const;

        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        bool              vert_is_saddle        (const uint vid, const int tex_coord = U_param) const;
        bool              vert_is_critical_p    (const uint vid, const int tex_coord = U_param) const;
        uint              vert_opposite_to      (const uint eid, const uint vid) const;
        double            vert_area             (const uint vid) const;
        double            vert_mass             (const uint vid) const;
        bool              verts_are_ordered_CCW (const uint fid, const uint curr, const uint prev) const;
        bool              vert_is_boundary      (const uint vid) const;
        std::vector<uint> vert_boundary_edges   (const uint vid) const;
        std::vector<uint> vert_ordered_vert_ring(const uint vid) const;
        std::vector<uint> vert_ordered_face_ring(const uint vid) const;
        std::vector<uint> vert_ordered_edge_ring(const uint vid) const;
        std::vector<uint> vert_ordered_edge_link(const uint vid) const;
        void              vert_ordered_one_ring (const uint          vid,
                                                 std::vector<uint> & v_ring,        // sorted list of adjacent vertices
                                                 std::vector<uint> & f_ring,        // sorted list of adjacent triangles
                                                 std::vector<uint> & e_ring,        // sorted list of edges incident to vid
                                                 std::vector<uint> & e_link) const; // sorted list of edges opposite to vid

        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        bool  edge_is_manifold(const uint eid) const;
        bool  edge_is_boundary(const uint eid) const;
        bool  edges_share_face(const uint eid1, const uint eid2) const;
        ipair edge_shared     (const uint fid0, const uint fid1) const;

        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

virtual double face_area          (const uint fid) const = 0;
        double face_mass          (const uint fid) const;
        int    face_shared        (const uint eid0, const uint eid1) const;
        int    face_adjacent_along(const uint fid, const uint vid0, const uint vid1) const;
        bool   face_is_boundary   (const uint fid) const;
        int    face_opposite_to   (const uint eid, const uint fid) const;

        //::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        vec3d  elem_vert        (const uint fid, const uint offset) const;
        uint   elem_vert_id     (const uint fid, const uint offset) const;
        uint   elem_vert_offset (const uint fid, const uint vid) const;
        vec3d  elem_centroid    (const uint fid) const;
        void   elem_show_all    ();
        double elem_mass        (const uint fid) const;
};

}

#ifndef  CINO_STATIC_LIB
#include "abstract_surface_mesh.cpp"
#endif

#endif //CINO_ABSTRACT_SURFACE_MESH_H
