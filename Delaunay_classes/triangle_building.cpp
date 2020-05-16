#include "./triangle_building.hpp"

		//método que determina o primeiro triangulo da triangulação:
		del::Triangle del::Triangle_building.point_based_triangle_building (del::Triangle_building.A)
		{

				//encontra vizinhança do ponto A:
				for (size_t k = 0; k < catalogo.size(); k++)
				{

					del::Triangle_building::P.p[0]=catalogo[k][0][0];
					del::Triangle_building::P.p[1]=catalogo[k][0][1];
					del::Triangle_building::P.p[2]=catalogo[k][0][2];
					if (del::Triangle_building::A == del::Triangle_building::P)
					{
						del::Triangle_building::VIZ_A = del::Triangle_building::k;
					}

				}
				//ponto B se localiza na segunda linha da vizinhança de A:

					del::Triangle_building::B.p[0]=catalogo[del::Triangle_building::VIZ_A][1][0];
					del::Triangle_building::B.p[1]=catalogo[del::Triangle_building::VIZ_A][1][1];
					del::Triangle_building::B.p[2]=catalogo[del::Triangle_building::VIZ_A][1][2];

				//encontra vizinhança do ponto B:
				for (size_t k = 0; k < catalogo.size(); k++)
				{

					del::Triangle_building::P.p[0]=catalogo[k][0][0];
					del::Triangle_building::P.p[1]=catalogo[k][0][1];
					del::Triangle_building::P.p[2]=catalogo[k][0][2];
					if (del::Triangle_building::B == del::Triangle_building::P)
					{
						del::Triangle_building::VIZ_B = k;
					}

				}


				// (do ... while loop) procura ponto C nas vizinhanças de A e B, monta triangulo, encontra esfera que circunscreve A, B e C e aplica método de Delaunay:
				do
				{

				for (size_t i = 0; i < 2; i++)
					{
						for (size_t j = 0; j < 3; j++)
						{
							del::Triangle_building::AB[i][j]=catalogo[del::Triangle_building::VIZ_A][i][j];
						}

					}
					//procura ponto que seja vizinho comum de A e B - ponto C:

					for (size_t linha_A = 0; linha_A < catalogo[del::Triangle_building::VIZ_A].size(); linha_A++)
					{
						for (size_t col_A = 0; col_A < 3; col_A++)
						{
							del::Triangle_building::P1.p[col_A] = catalogo[del::Triangle_building::VIZ_A][linha_A][col_A];
							for (size_t linha_B = 0; linha_B < catalogo[del::Triangle_building::VIZ_B].size(); linha_B++)
							{
								for (size_t col_B = 0; col_B < 3; col_B++)
								{
									del::Triangle_building::P2.p[col_B] = catalogo[del::Triangle_building::VIZ_B][linha_B][col_B];

									//se P1 == P2 então este é o PONTO C:
									if ( (del::Triangle_building::P1 == del::Triangle_building::P2) && (del::Triangle_building::P1 != del::Triangle_building::A) && (del::Triangle_building::P1 != del::Triangle_building::B) )
									{
										del::Triangle_building::C = del::Triangle_building::P1;

										//monta triangulo ABC numa matriz: candidato à triangulação de Delaunay

										del::Triangle_building::ABC[0][0]=del::Triangle_building::A[0];
										del::Triangle_building::ABC[0][1]=del::Triangle_building::A[1];
										del::Triangle_building::ABC[0][2]=del::Triangle_building::A[2];

										del::Triangle_building::ABC[1][0]=del::Triangle_building::B[0];
										del::Triangle_building::ABC[1][1]=del::Triangle_building::B[1];
										del::Triangle_building::ABC[1][2]=del::Triangle_building::B[2];

										del::Triangle_building::ABC[2][0]=del::Triangle_building::P1.p[2];
										del::Triangle_building::ABC[2][0]=del::Triangle_building::P1.p[0];
										del::Triangle_building::ABC[2][1]=del::Triangle_building::P1.p[1];


										for (int j = 0; j < 3; j++) {
											del::Triangle_building::find_center_sphere_obj.A[j]= del::Triangle_building::ABC[0][j];    //faz passagem por valor dos pontos A, B e C
											del::Triangle_building::find_center_sphere_obj.B[j]= del::Triangle_building::ABC[1][j];       // para o objeto find_center_sphere_obj
											del::Triangle_building::find_center_sphere_obj.C[j]= del::Triangle_building::ABC[2][j];
										}
										for (int i = 0; i < 3; i++) //encontra centro da esfera
											{
												del::Triangle_building::Centro_Circunf_ABC.p[i]= del::Triangle_building::find_center_sphere_obj.centro[i];
											}
										del::Triangle_building::Raio = del::Triangle_building::find_center_sphere_obj.Raio; //guarda raio da esfera

												for (size_t k = 0; k < catalogo.size(); k++) // encontra vizinhança do ponto C
												{

													del::Triangle_building::P.p[0]=catalogo[k][0][0];
													del::Triangle_building::P.p[1]=catalogo[k][0][1];
													del::Triangle_building::P.p[2]=catalogo[k][0][2];
													if (P1 == P)
														{
															del::Triangle_building::VIZ_C = k;
														}
												}
												//procurando pontos da vizinhança de A dentro da esfera:
												for (size_t i = 2; i < catalogo[del::Triangle_building::VIZ_A].size(); i++)
												{
													del::Triangle_building::P.p[0]=catalogo[del::Triangle_building::VIZ_A][i][0];
													del::Triangle_building::P.p[1]=catalogo[del::Triangle_building::VIZ_A][i][1];
													del::Triangle_building::P.p[2]=catalogo[del::Triangle_building::VIZ_A][i][2];
													del::Triangle_building::d= P.distancia(Centro_Circunf_ABC);
													if ((d<Raio) && (del::Triangle_building::P! == del::Triangle_building::A)&& (del::Triangle_building::P! == del::Triangle_building::B)&& (del::Triangle_building::P! == del::Triangle_building::C))
													{
														del::Triangle_building::encontrou = true;
														break;
													}

												}
												if (del::Triangle_building::encontrou)
												{
													break;
												}

												//procurando pontos da vizinhança de B dentro da esfera:
												for (size_t i = 1; i < catalogo[del::Triangle_building::VIZ_B].size(); i++)
												{
													P.p[0]=catalogo[del::Triangle_building::VIZ_B][i][0];
													P.p[1]=catalogo[del::Triangle_building::VIZ_B][i][1];
													P.p[2]=catalogo[del::Triangle_building::VIZ_B][i][2];
													d= P.distancia(del::Triangle_building::Centro_Circunf_ABC);
													if ((d<Raio) && (P! == A)&& (P! == B)&& (P! == C))
													{
														del::Triangle_building::encontrou = true;
														break;
													}
												}
												if (del::Triangle_building::encontrou)
												{
													break;
												}
												//procurando pontos da vizinhança de C dentro da esfera:
												for (size_t i = 1; i < catalogo[del::Triangle_building::VIZ_C].size(); i++)
												{
													P.p[0]=catalogo[del::Triangle_building::VIZ_C][i][0];
													P.p[1]=catalogo[del::Triangle_building::VIZ_C][i][1];
													P.p[2]=catalogo[del::Triangle_building::VIZ_C][i][2];
													d= P.distancia(del::Triangle_building::Centro_Circunf_ABC);
													if ((del::Triangle_building::d<del::Triangle_building::Raio) && (del::Triangle_building::P! == del::Triangle_building::A)&& (del::Triangle_building::P! == del::Triangle_building::B)&& (del::Triangle_building::P! == del::Triangle_building::C))
													{
														del::Triangle_building::encontrou = true;
														break;
													}
													else
													{
														del::Triangle_building::encontrou = false;
													}

												}
												if (del::Triangle_building::encontrou)
												{
													break;
												}
									}

								}
							}
						}
					}







				}while(!del::Triangle_building::encontrou);

				//triangulo ABC é admitido na triangulação

				del::Triangle_building::T.A = del::Triangle_building::A;
				del::Triangle_building::T.B = del::Triangle_building::B;
				del::Triangle_building::T.C = del::Triangle_building::C;

				return del::Triangle_building::T;


		} //Fim do método "point_based_triangle_building"


		del::Triangle del::Triangle_building::edge_based_triangle_building (del::Edge edge, del::Triangle Not_this_triangle)
		{

				del::Triangle_building::A = edge.first_point;
				del::Triangle_building::B = edge.second_point;

				//encontra vizinhança do ponto A:
				for (size_t k = 0; k < catalogo.size(); k++)
				{

					del::Triangle_building::P.p[0]=catalogo[k][0][0];
					del::Triangle_building::P.p[1]=catalogo[k][0][1];
									del::Triangle_building::P.p[2]=catalogo[k][0][2];
					if (del::Triangle_building::A == del::Triangle_building::P)
					{
						del::Triangle_building::VIZ_A = k;
					}

				}


				//encontra vizinhança do ponto B:
				for (size_t k = 0; k < catalogo.size(); k++)
				{

					del::Triangle_building::P.p[0]=catalogo[k][0][0];
					del::Triangle_building::P.p[1]=catalogo[k][0][1];
					del::Triangle_building::P.p[2]=catalogo[k][0][2];
					if (del::Triangle_building::B == del::Triangle_building::P)
					{
						del::Triangle_building::VIZ_B = k;
					}

				}



				do
				{

					for (size_t linha_A = 0; linha_A < catalogo[VIZ_A].size(); linha_A++)//BUSCA DO PONTO C
					{
						for (size_t col_A = 0; col_A < 3; col_A++)//BUSCA DO PONTO C
						{
							P1.p[col_A] = catalogo[VIZ_A][linha_A][col_A];
							for (size_t linha_B = 0; linha_B < catalogo[VIZ_B].size(); linha_B++)//BUSCA DO PONTO C
							{
								for (size_t col_B = 0; col_B < 3; col_B++)//BUSCA DO PONTO C
								{
									P2.p[col_B] = catalogo[VIZ_B][linha_B][col_B];
									if ( (P1 == P2) && (P1 != A) && (P1 != B) ) //P1 == P2 é o PONTO C !!!
									{
										C = P1;
										//monta triangulo ABC: candidato à triangulação de Delaunay
										del::Triangle_building::ABC[0][0]=del::Triangle_building::A[0];
										del::Triangle_building::ABC[0][1]=del::Triangle_building::A[1];
										del::Triangle_building::ABC[0][2]=del::Triangle_building::A[2];

										del::Triangle_building::ABC[1][0]=del::Triangle_building::B[0];
										del::Triangle_building::ABC[1][1]=del::Triangle_building::B[1];
										del::Triangle_building::ABC[1][2]=del::Triangle_building::B[2];

										del::Triangle_building::ABC[2][0]=del::Triangle_building::P1.p[2];
										del::Triangle_building::ABC[2][0]=del::Triangle_building::P1.p[0];
										del::Triangle_building::ABC[2][1]=del::Triangle_building::P1.p[1];


										for (int j = 0; j < 3; j++)
										{
											del::Triangle_building::find_center_sphere_obj.C[j]= del::Triangle_building::ABC[2][j];
											del::Triangle_building::find_center_sphere_obj.A[j]= del::Triangle_building::ABC[0][j];    //faz passagem por valor dos pontos A, B e C
										}
										for (int i = 0; i < 3; i++) //encontra centro da esfera
										{
											del::Triangle_building::Centro_Circunf_ABC.p[i]= del::Triangle_building::find_center_sphere_obj.centro[i];
										}
										del::Triangle_building::Raio = find_center_sphere_obj.Raio; //guarda raio da esfera
										del::Triangle_building::find_center_sphere_obj.B[j]= del::Triangle_building::ABC[1][j];       // para o objeto find_center_sphere_obj

										for (size_t k = 0; k < catalogo.size(); k++) // encontra vizinhança do ponto C
										{
											del::Triangle_building::P.p[0]=catalogo[k][0][0];
											del::Triangle_building::P.p[1]=catalogo[k][0][1];
											del::Triangle_building::P.p[2]=catalogo[k][0][2];
											if (P1 == P)
											{
												del::Triangle_building::VIZ_C = k;
											}
										}

										//procurando pontos da vizinhança de A dentro da esfera:
										for (size_t i = 2; i < catalogo[del::Triangle_building::VIZ_A].size(); i++)
										{
											del::Triangle_building::P.p[0]=catalogo[del::Triangle_building::VIZ_A][i][0];
											del::Triangle_building::P.p[1]=catalogo[del::Triangle_building::VIZ_A][i][1];
											del::Triangle_building::P.p[2]=catalogo[del::Triangle_building::VIZ_A][i][2];
											del::Triangle_building::d= del::Triangle_building::P.distancia(del::Triangle_building::Centro_Circunf_ABC);
											if ((d<Raio) && (P! == A)&& (P! == B)&& (P! == C))
											{
												del::Triangle_building::encontrou_ponto_dentro_da_esfera = true; //caso isso for verdadeiro, o programa deve continuar a busca por outro ponto C
												break;
											}

										}
											if (del::Triangle_building::encontrou_ponto_dentro_da_esfera)
											{
												break;
											}

										//procurando pontos da vizinhança de B dentro da esfera:
										for (size_t i = 1; i < catalogo[VIZ_B].size(); i++)
										{
											del::Triangle_building::P.p[0]=catalogo[del::Triangle_building::VIZ_B][i][0];
											del::Triangle_building::P.p[1]=catalogo[del::Triangle_building::VIZ_B][i][1];
											del::Triangle_building::P.p[2]=catalogo[del::Triangle_building::VIZ_B][i][2];
											del::Triangle_building::d= del::Triangle_building::P.distancia(del::Triangle_building::Centro_Circunf_ABC);
											if ((del::Triangle_building::d<del::Triangle_building::Raio) && (del::Triangle_building::P! == del::Triangle_building::A)&& (del::Triangle_building::P! == B)&& (del::Triangle_building::P! == del::Triangle_building::C))
											{
												del::Triangle_building::encontrou_ponto_dentro_da_esfera = true; //caso isso for verdadeiro, o programa deve continuar a busca por outro ponto C
												break;
											}
										}

										if (del::Triangle_building::encontrou_ponto_dentro_da_esfera)
										{
											break;
										}

										//procurando pontos da vizinhança de C dentro da esfera:
										for (size_t i = 1; i < catalogo[del::Triangle_building::VIZ_C].size(); i++)
										{
											del::Triangle_building::P.p[0]=catalogo[del::Triangle_building::VIZ_C][i][0];
											del::Triangle_building::P.p[1]=catalogo[del::Triangle_building::VIZ_C][i][1];
											del::Triangle_building::P.p[2]=catalogo[del::Triangle_building::VIZ_C][i][2];
											del::Triangle_building::d= del::Triangle_building::P.distancia(del::Triangle_building::Centro_Circunf_ABC);
											if ((del::Triangle_building::d<del::Triangle_building::Raio) && (del::Triangle_building::P! == del::Triangle_building::A)&& (del::Triangle_building::P! == del::Triangle_building::B)&& (del::Triangle_building::P! == del::Triangle_building::C))
											{
												del::Triangle_building::encontrou_ponto_dentro_da_esfera = true; //caso isso for verdadeiro, o programa deve continuar a busca por outro ponto C
												break;
											}
											else
											{
													//SE NENHUM PONTO FOR ENCONTRADO NO INTERIOR DA ESFERA QUE CIRCUNSCREVE O TRIANGULO ABC,
																					//CONSTRUA New_triangle E COMPARE COM O 'not_this_triangle' fornecido no argumento deste método

												del::Triangle_building::New_triangle.A = del::Triangle_building::A;
												del::Triangle_building::New_triangle.B = del::Triangle_building::B;
												del::Triangle_building::New_triangle.C = del::Triangle_building::C;

												if (del::Triangle_building::New_triangle == Ndel::Triangle_building::ot_this_triangle)
												{
													break;
												}
												else //caso sejam diferentes, New_triangle é cuspido como resultado e a busca é terminada (sai do 'do ... while' loop)
												{
													del::Triangle_building::encontrou_triangulo_valido = true;
												}


											}

										}


										if (del::Triangle_building::encontrou_ponto_dentro_da_esfera)
										{
											break; //continua busca por ponto C
										}
									}
								}
							}
						}
					}//fim do loop de varredura na vizinhança de A ... FIM DA BUSCA PELO PONTO C



					//contemplando caso em que nenhum ponto C satisfaz a condição de Delaunay:
					//(se varreu as vizinhanças de A e B e não encontrou qqr C então construa o 'triangulo" trivial) --- neste caso o edge deve ser reconhecido como um membro definitivo do convex_hull
					if ((linha_A == catalogo[VIZ_A].size()-1) && (linha_B == catalogo[VIZ_B].size()-1) && (!encontrou_ponto_dentro_da_esfera))
					{


						del::Triangle_building::Origem.p[0]=0.0;
						del::Triangle_building::Origem.p[1]=0.0;
						del::Triangle_building::Origem.p[2]=0.0;
						del::Triangle_building::New_triangle.A = del::Triangle_building::Origem;
						del::Triangle_building::New_triangle.B = del::Triangle_building::Origem;
						del::Triangle_building::New_triangle.C = del::Triangle_building::Origem;

						del::Triangle_building::encontrou_triangulo_valido = true; //sai do loop 'do...while' e método retorna o triangulo trivial
					}



				}while(!del::Triangle_building::encontrou_triangulo_valido);//fim do ... while loop


		return del::Triangle_building::New_triangle;

		} //Fim do método "edge_based_triangle_building"


					//caso o triangulo seja admitido na triangulação, ENTÃO determina orientação correta dos vértices
		//faz segunda busca por triangulo de Delaunay nas vizinhanças de A e B.
			//Se encontrar segundo triangulo de Delaunay, então aresta AB é colocada no conjunto de arestas internas.
			//Se não encontrar segundo triângulo de Delaunay, então aresta é colocada no conjunto de arestas de borda.
