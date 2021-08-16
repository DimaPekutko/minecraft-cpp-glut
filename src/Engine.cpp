#include "Engine.hpp"  

namespace Engine {
	GameInterface* _gameInterface;
	Scene* _scene;
	Player* _player;
	RayCaster* _rayCaster;

	int _lastMouseX, _lastMouseY;

	bool _mouseMoved = false;

	void _setPerspectiveView() {
		glLoadIdentity();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60,16.0/9.0,1,75);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnable(GL_DEPTH_TEST);
	}

	void _rayCast() {
		if(!_mouseMoved)
			return;
		auto camPos = _player->getPlayerCameraPos();
		std::vector<GameObject*> hittedObjects = _rayCaster->rayCast(camPos, _scene->getGameObjects());
		_scene->setSelectedObject(camPos, hittedObjects);
		_mouseMoved = false;
	}

	void _renderEngine() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			_setPerspectiveView();
			
			_player->checkCollisionWithObjects(_scene->getGameObjects());
			_player->draw();
			_scene->render();

			// this need to start raycast only after perspective camera setting
			_rayCast();
			
			_gameInterface->draw();
		glutSwapBuffers();
	}

	void _timerLoop(int value) {
		glutPostRedisplay();
		glutWarpPointer(GameConfigs::CURRENT_WIDTH/2, GameConfigs::CURRENT_HEIGHT/2);
    	glutTimerFunc(1000/60,_timerLoop,0);
	}

	void _onKeyPressEngine(unsigned char key, int x, int y) {
		if (key == GameConfigs::KEYBOARD_FORWARD) {
			_player->moveForward();
		}
		else if(key == GameConfigs::KEYBOARD_RIGHT) {
			_player->moveRight();
		}
		else if(key == GameConfigs::KEYBOARD_BACK) {
			_player->moveBack();
		}
		else if(key == GameConfigs::KEYBOARD_LEFT) {
			_player->moveLeft();
		}
		else if(key == GameConfigs::KEYBOARD_SPACE) {
			_player->jump();
		}
		glutPostRedisplay();
	}

	void _onKeyUpEngine(unsigned char key, int x, int y) {
		if (key == GameConfigs::KEYBOARD_FORWARD) {
			_player->moveForward(false);
		}
		else if(key == GameConfigs::KEYBOARD_RIGHT) {
			_player->moveRight(false);
		}
		else if(key == GameConfigs::KEYBOARD_BACK) {
			_player->moveBack(false);
		}
		else if(key == GameConfigs::KEYBOARD_LEFT) {
			_player->moveLeft(false);
		} 
		glutPostRedisplay();
	}
	
	void _onSpecialKeyPressEngine(int keyCode, int x, int y) {
		// if(keyCode == GameConfigs::KEYBOARD_PLAYER_BOOST_KEY_CODE)
		// 	_player->setBoost();
		// else if(keyCode == GameConfigs::KEYBOARD_DEBUG_MODE_KEY_CODE) {
		// 	GameConfigs::debugMode ? 
		// 		GameConfigs::debugMode = false :
		// 		GameConfigs::debugMode = true;
		// }
	}
    
	void _onSpecialKeyUpEngine(int keyCode, int x, int y) {
		// if(keyCode == GameConfigs::KEYBOARD_PLAYER_BOOST_KEY_CODE)
			// _player->setBoost(false);
	}

	void _onMouseMove(int x, int y) {
		if(_lastMouseX == x && _lastMouseY == y)
			return;
		_player->rotateCamera(x, y);
		_mouseMoved = true;		
		_lastMouseX = x;
		_lastMouseY = y;
		glutPostRedisplay();
	}

	void _onMouseClick(int btn, int state, int x, int y) {
		// destroy object
		if(btn == GLUT_LEFT_BUTTON) {
			if(state == GLUT_DOWN) {
				_scene->setDestructionStatus(true);
			}
			else if(state == GLUT_UP) {
				_scene->setDestructionStatus(false);
			} 
		}
		// build object
		else if(btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && _scene->selectedObjectExist()) {
			BlockType block;
			bool blockTakenFromInv = _player->getInventory()->getSelectedBlockType(&block);
			if(blockTakenFromInv) {
				if(state == GLUT_DOWN) {
					_scene->buildBlock(block);
				} 
			}
		}
		else if((btn == 3 || btn == 4) && state == GLUT_DOWN) {
			int selectedIndex = _player->getInventory()->getSelectedSlotIndex();
			btn == 3 ? selectedIndex-- : selectedIndex++;
			_player->getInventory()->setSlotSelectedIndex(selectedIndex);
		}
	}

	void _onWindowReshape(int w, int h) {
		GameConfigs::CURRENT_WIDTH = w;
		GameConfigs::CURRENT_HEIGHT = h;
		glViewport(0,0,w,h);
		_setPerspectiveView();
	}

	void _generateTerrain() {
		int SIZE = 50;
		for(int i = 0; i < SIZE; i++) {
			for(int j = 0; j < SIZE; j++) {
				_scene->addToScene(new Cube(i,0,-j, BlockTypes::PLANKS_BLOCK_TYPE));
			}
		}
		_scene->addToScene(new Cube(10,1,-10, BlockTypes::DIRT_BLOCK_TYPE));
		_scene->addToScene(new Cube(10,2,-10, BlockTypes::DIRT_BLOCK_TYPE));
		_scene->addToScene(new Cube(10,3,-10, BlockTypes::DIRT_BLOCK_TYPE));
		_scene->addToScene(new Cube(10,4,-10, BlockTypes::DIRT_BLOCK_TYPE));
		_scene->addToScene(new Cube(10,5,-10, BlockTypes::DIRT_BLOCK_TYPE));
	}

	void _loadTextures() {
		auto blocksTextureAtlas = new TextureAtlas("./assets/blocks_texture_atlas.png");
		// setting static texture atlas field for every cube object 
		Cube::setBlocksTextureAtlas(blocksTextureAtlas);
		_gameInterface->setBlocksTextureAtlas(blocksTextureAtlas);
	}

	void _initialize() {
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowSize(GameConfigs::initWindowWidth, GameConfigs::initWindowHeight);
		glutCreateWindow(GameConfigs::gameTitle);
		glutSetCursor(GLUT_CURSOR_NONE);
		glutWarpPointer(GameConfigs::CURRENT_WIDTH/2, GameConfigs::CURRENT_HEIGHT/2);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(0.4,0.3,1,0.0);
		glEnable( GL_BLEND );
		glEnable(GL_DEPTH_TEST);
    	glDepthFunc(GL_LEQUAL);
		glutDisplayFunc(_renderEngine);
		glutKeyboardFunc(_onKeyPressEngine);
		glutKeyboardUpFunc(_onKeyUpEngine);
		glutSpecialFunc(_onSpecialKeyPressEngine);
		glutSpecialUpFunc(_onSpecialKeyUpEngine);
		glutMotionFunc(_onMouseMove);
		glutPassiveMotionFunc(_onMouseMove);
		glutMouseFunc(_onMouseClick);
		glutReshapeFunc(_onWindowReshape);
		glutFullScreen();
		glutTimerFunc(0, _timerLoop, 1);
    
		// gluLookAt()
		_scene = new Scene();
		_player = new Player(5,15,-5);
		_rayCaster = new RayCaster();
		_gameInterface = new GameInterface(_player);
		// _scene->addToScene(_player);
		_loadTextures();
		_generateTerrain();
		// glRotatef(60, 1, 0, 0);
		
	}

	void start(int &argc, char **argv) {
		glutInit(&argc, argv);
		_initialize();
		// glTranslatef(0,-25,0);
		// glTranslatef(0,-3,-10);
		// glRotatef(30,0,1,0);
		glutMainLoop();
	}
}