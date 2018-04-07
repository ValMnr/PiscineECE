#include "graph.h"
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <queue>
#include <limits.h>
#include <limits>

/***************************************************
                    VERTEX
****************************************************/

/// Le constructeur met en place les �l�ments de l'interface
VertexInterface::VertexInterface(int idx, int x, int y, std::string pic_name, int rtm)
{
    // La boite englobante
    m_top_box.set_pos(x, y);
    m_top_box.set_dim(130, 100);
    m_top_box.set_moveable();

    // Le slider de r�glage de valeur
    m_top_box.add_child( m_slider_value );
    m_slider_value.set_range(0.0, 100.0);  // Valeurs arbitraires, � adapter...
    m_slider_value.set_dim(20,80);
    m_slider_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);

    // Label de visualisation de valeur
    m_top_box.add_child( m_label_value );
    m_label_value.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Down);

    // Une illustration...
    if (pic_name!="")
    {
        m_top_box.add_child( m_img );
        m_img.set_pic_name(pic_name);
        m_img.set_rtm(rtm);
        m_img.set_gravity_x(grman::GravityX::Right);
    }

    // Label de visualisation d'index du sommet dans une boite
    m_top_box.add_child( m_box_label_idx );
    m_box_label_idx.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Down);
    m_box_label_idx.set_dim(20,12);
    m_box_label_idx.set_bg_color(BLANC);

    m_box_label_idx.add_child( m_label_idx );
    m_label_idx.set_message( std::to_string(idx) );
}


/// Gestion du Vertex avant l'appel � l'interface
void Vertex::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donn�e m_value vers le slider associ�
    m_interface->m_slider_value.set_value(m_value);

    /// Copier la valeur locale de la donn�e m_value vers le label sous le slider
    m_interface->m_label_value.set_message( std::to_string( (int)m_value) );
}


/// Gestion du Vertex apr�s l'appel � l'interface
void Vertex::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donn�e m_value locale
    m_value = m_interface->m_slider_value.get_value();
}



/***************************************************
                    EDGE
****************************************************/

/// Le constructeur met en place les �l�ments de l'interface
EdgeInterface::EdgeInterface(Vertex& from, Vertex& to)
{
    // Le WidgetEdge de l'interface de l'arc
    if ( !(from.m_interface && to.m_interface) )
    {
        std::cerr << "Error creating EdgeInterface between vertices having no interface" << std::endl;
        throw "Bad EdgeInterface instanciation";
    }
    m_top_edge.attach_from(from.m_interface->m_top_box);
    m_top_edge.attach_to(to.m_interface->m_top_box);
    m_top_edge.reset_arrow_with_bullet();

    // Une boite pour englober les widgets de r�glage associ�s
    m_top_edge.add_child(m_box_edge);
    m_box_edge.set_dim(24,60);
    m_box_edge.set_bg_color(BLANCBLEU);

    // Le slider de r�glage de valeur
    m_box_edge.add_child( m_slider_weight );
    m_slider_weight.set_range(0.0, 100.0);  // Valeurs arbitraires, � adapter...
    m_slider_weight.set_dim(16,40);
    m_slider_weight.set_gravity_y(grman::GravityY::Up);

    // Label de visualisation de valeur
    m_box_edge.add_child( m_label_weight );
    m_label_weight.set_gravity_y(grman::GravityY::Down);

}


/// Gestion du Edge avant l'appel � l'interface
void Edge::pre_update()
{
    if (!m_interface)
        return;

    /// Copier la valeur locale de la donn�e m_weight vers le slider associ�
    m_interface->m_slider_weight.set_value(m_weight);

    /// Copier la valeur locale de la donn�e m_weight vers le label sous le slider
    m_interface->m_label_weight.set_message( std::to_string( (int)m_weight ) );
}

/// Gestion du Edge apr�s l'appel � l'interface
void Edge::post_update()
{
    if (!m_interface)
        return;

    /// Reprendre la valeur du slider dans la donn�e m_weight locale
    m_weight = m_interface->m_slider_weight.get_value();
}



/***************************************************
                    GRAPH
****************************************************/

/// Ici le constructeur se contente de pr�parer un cadre d'accueil des
/// �l�ments qui seront ensuite ajout�s lors de la mise ne place du Graphe
GraphInterface::GraphInterface(int x, int y, int w, int h)
{
    m_top_box.set_dim(1000,740);
    m_top_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);

    m_top_box.add_child(m_tool_box);
    m_tool_box.set_dim(80,720);
    m_tool_box.set_gravity_xy(grman::GravityX::Left, grman::GravityY::Up);
    m_tool_box.set_bg_color(BLANCBLEU);

    m_top_box.add_child(m_main_box);
    m_main_box.set_dim(908,720);
    m_main_box.set_gravity_xy(grman::GravityX::Right, grman::GravityY::Up);
    m_main_box.set_bg_color(BLANCJAUNE);
}


/// M�thode sp�ciale qui construit un graphe arbitraire (d�mo)
/// Cette m�thode est � enlever et remplacer par un syst�me
/// de chargement de fichiers par exemple.
/// Bien s�r on ne veut pas que vos graphes soient construits
/// "� la main" dans le code comme �a.
void Graph::make_example()
{
    m_interface = std::make_shared<GraphInterface>(50, 0, 750, 600);
    // La ligne pr�c�dente est en gros �quivalente � :
    // m_interface = new GraphInterface(50, 0, 750, 600);

    /// Les sommets doivent �tre d�finis avant les arcs


    int nb_som, nb_arete, nb_pop;
    int index_arete,som_dep, som_arrive, coeff;
    int index, x, y, cap_port, croissance, rtm;
    int i=0;
    int j=0;
    std::string nom;
    std::string nom_fichier;


    std::ifstream fic("graph2.txt", std::ios::in);


    if(fic)
    {
        Graph g;
        fic >> nb_som >> nb_arete;
        fic.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        do
        {
            /// REMPLISSAGE des sommets
            fic >> index >> nb_pop >> x >> y >> nom_fichier >> cap_port>> rtm; //>> croissance;
            //std::cout<<index<<std::endl;
            add_interfaced_vertex(index, nb_pop, x, y, nom_fichier, cap_port, rtm);
            i++;
        }
        while( i<nb_som);
        //m_fname
        fic.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        /*do
        {
            /// REMPLISSAGE des aretes

            fic >> index_arete >> som_dep >> som_arrive >> coeff;
            add_interfaced_edge(index_arete, som_dep, som_arrive, coeff);
            std::cout<<index_arete<<std::endl;
            j++;
        }

        while(!fic.eof() || j<nb_arete);
        */
        m_index1=nb_som;
        m_index2=nb_arete;
        for(j=0; j<nb_arete; j++)
        {
            fic >> index_arete >> som_dep >> som_arrive >> coeff;

            add_interfaced_edge(index_arete, som_dep, som_arrive, coeff);
            //std::cout<<index_arete<<std::endl;
        }



        fic.close();

    }


}

/// La m�thode update � appeler dans la boucle de jeu pour les graphes avec interface
void Graph::update()
{
    if (!m_interface)
        return;

    for (auto &elt : m_vertices)
        elt.second.pre_update();

    for (auto &elt : m_edges)
        elt.second.pre_update();

    m_interface->m_top_box.update();

    for (auto &elt : m_vertices)
        elt.second.post_update();

    for (auto &elt : m_edges)
        elt.second.post_update();



}

/// Aide � l'ajout de sommets interfac�s
void Graph::add_interfaced_vertex(int idx, int value, int x, int y, std::string pic_name, int rtm, int K)
{
    if ( m_vertices.find(idx)!=m_vertices.end() )
    {
        std::cerr << "Error adding vertex at idx=" << idx << " already used..." << std::endl;
        throw "Error adding vertex";
    }
    // Cr�ation d'une interface de sommet
    VertexInterface *vi = new VertexInterface(idx, x, y, pic_name, rtm);
    // Ajout de la top box de l'interface de sommet
    m_interface->m_main_box.add_child(vi->m_top_box);
    // On peut ajouter directement des vertices dans la map avec la notation crochet :
    m_vertices[idx] = Vertex(value, vi);
}

/// Aide � l'ajout d'arcs interfac�s
void Graph::add_interfaced_edge(int idx, int id_vert1, int id_vert2, int weight)
{
    if ( m_edges.find(idx)!=m_edges.end() )
    {
        std::cerr << "Error adding edge at idx=" << idx << " already used..." << std::endl;
        throw "Error adding edge";
    }

    if ( m_vertices.find(id_vert1)==m_vertices.end() || m_vertices.find(id_vert2)==m_vertices.end() )
    {
        std::cerr << "Error adding edge idx=" << idx << " between vertices " << id_vert1 << " and " << id_vert2 << " not in m_vertices" << std::endl;
        throw "Error adding edge";
    }

    EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]);
    m_interface->m_main_box.add_child(ei->m_top_edge);
    m_edges[idx] = Edge(weight, ei);
    m_edges[idx].m_from = id_vert1;
    m_edges[idx].m_to = id_vert2;
    /*m_vertices[id_vert1].m_out.push_back(id_vert2);
    m_vertices[id_vert2].m_in.push_back(id_vert1);*/
    m_vertices[id_vert1].m_out.push_back(idx);
    m_vertices[id_vert2].m_in.push_back(idx);
}

void Graph::save(int idv, int ided)
{
    std::ofstream  fic(/*file_name*/ "graph2.txt", std::ios::out | std::ios::trunc);
    int j=0;
    if(fic)
    {

        fic<< m_vertices.size()<<std::endl;
        fic << m_edges.size() << std::endl;

        for(int i=0; i<m_vertices.size(); i++)
        {
            if(i!=idv)
            {
                fic << i << " " << m_vertices[i+j].m_value << " " << m_vertices[i+j].m_interface->m_top_box.get_posx() << " " << m_vertices[i+j].m_interface->m_top_box.get_posy() << " " << m_vertices[i+j].m_interface->m_img.get_name_pic()<< " "<<m_vertices[i+j].m_rtm<<" "<<m_vertices[i+j].m_K <<std::endl;
            }
                if(i==idv)
            {
                j++;
                fic << i << " " << m_vertices[i+j].m_value << " " << m_vertices[i+j].m_interface->m_top_box.get_posx() << " " << m_vertices[i+j].m_interface->m_top_box.get_posy() << " " << m_vertices[i+j].m_interface->m_img.get_name_pic()<< " "<<m_vertices[i+j].m_rtm<<" "<<m_vertices[i+j].m_K <<std::endl;
            }
            }

j=0;
            for(int i=0; i<m_edges.size(); i++)
            {

                if(m_edges[i].m_weight!=0)
                {

                    /*if((m_edges[i].m_from==m_edges[i-j].m_from)&&(m_edges[i-j].m_to==m_edges[i-j].m_to))
                        {
                            fic << i << " " << m_edges[i+j].m_from << " " << m_edges[i+j].m_to << " " << m_edges[i+j].m_weight << std::endl;
                        }
                        else fic << i << " " << m_edges[i].m_from << " " << m_edges[i].m_to << " " << m_edges[i].m_weight << std::endl;*/
                  fic << j << " " << m_edges[i].m_from << " " << m_edges[i].m_to << " " << m_edges[i].m_weight << std::endl;
                j++;
                }

               /* else
                {

                    fic<< i-j <<" "<<m_edges[i+j].m_from<<" "<<m_edges[i+j].m_to<<" "<<m_edges[i+j].m_weight<<std::endl;

                }

                /*if(i!=ided && !idv)
                {
                    fic << i << " " << m_edges[i+j].m_from << " " << m_edges[i+j].m_to << " " << m_edges[i+j].m_weight << std::endl;
                }
                if(i==ided && idv)
                {
                    j++;
                    fic << i << " " << m_edges[i+j].m_from << " " << m_edges[i+j].m_to << " " << m_edges[i+j].m_weight << std::endl;
                }*/
            }







            fic.close();
        }
        else
            std::cout<<"erreur ouverture fichier"<<std::endl;



    }
    void Graph::test_remove_edge(int eidx)
    {
/// r�f�rence vers le Edge � enlever
        Edge &remed=m_edges.at(eidx);

        std::cout << "Removing edge " << eidx << " " << remed.m_from << "->" << remed.m_to << " " << remed.m_weight << std::endl;

/// Tester la coh�rence : nombre d'arc entrants et sortants des sommets 1 et 2
        std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
        std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
        std::cout << m_edges.size() << std::endl;

/// test : on a bien des �l�ments interfac�s
        if (m_interface && remed.m_interface)
        {
/// Ne pas oublier qu'on a fait �a � l'ajout de l'arc :
            /* EdgeInterface *ei = new EdgeInterface(m_vertices[id_vert1], m_vertices[id_vert2]); */
            /* m_interface->m_main_box.add_child(ei->m_top_edge); */
            /* m_edges[idx] = Edge(weight, ei); */
/// Le new EdgeInterface ne n�cessite pas de delete car on a un shared_ptr
/// Le Edge ne n�cessite pas non plus de delete car on n'a pas fait de new (s�mantique par valeur)
/// mais il faut bien enlever le conteneur d'interface m_top_edge de l'arc de la main_box du graphe
            m_interface->m_main_box.remove_child( remed.m_interface->m_top_edge );
        }

/// Il reste encore � virer l'arc supprim� de la liste des entrants et sortants des 2 sommets to et from !
/// References sur les listes de edges des sommets from et to
        std::vector<int> &vefrom = m_vertices[remed.m_from].m_out;
        std::vector<int> &veto = m_vertices[remed.m_to].m_in;
        /* vefrom.erase( std::remove( vefrom.begin(), vefrom.end(), eidx ), vefrom.end() );
         veto.erase( std::remove( veto.begin(), veto.end(), eidx ), veto.end() );*/

/// Le Edge ne n�cessite pas non plus de delete car on n'a pas fait de new (s�mantique par valeur)
/// Il suffit donc de supprimer l'entr�e de la map pour supprimer � la fois l'Edge et le EdgeInterface
/// mais malheureusement ceci n'enlevait pas automatiquement l'interface top_edge en tant que child de main_box !
        m_edges.erase(eidx);

/// Tester la coh�rence : nombre d'arc entrants et sortants des sommets 1 et 2
        std::cout << m_vertices[remed.m_from].m_in.size() << " " << m_vertices[remed.m_from].m_out.size() << std::endl;
        std::cout << m_vertices[remed.m_to].m_in.size() << " " << m_vertices[remed.m_to].m_out.size() << std::endl;
        std::cout << m_edges.size() << std::endl;

    }
    void Graph::remove_vertex(int ideix)
    {

        Vertex &remed=m_vertices.at(ideix);
        if(m_interface && remed.m_interface)
        {
            m_interface->m_main_box.remove_child( remed.m_interface->m_top_box );

            for(int i=m_vertices[ideix].m_in.size()-1; i>=0; i--)
            {
                test_remove_edge(m_vertices[ideix].m_in[i]);
            }
            for(int i=m_vertices[ideix].m_out.size()-1; i>=0; i--)
            {
                test_remove_edge(m_vertices[ideix].m_out[i]);
            }
            m_vertices.erase(ideix);
        }
    }




