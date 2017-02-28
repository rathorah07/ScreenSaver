#ifndef KEY_MOUSE_FUNC_H
#define KEY_MOUSE_FUNC_H

bool check_selection(float x , float y, int i);
void keyboard(unsigned char key, int x, int y);
void special_key(int key,int x,int y);
void mouse(int state, int button, int x, int y);

#endif
