CXX=g++
LD=g++
CFLAGS = -Wall -pedantic -Wextra -Werror -std=c++17
BUILD_DIR = build
SRC_DIR = src
BIN_NAME = td

all: MakeBuild towerdefense doc

compile: MakeBuild towerdefense

run:
	./$(BIN_NAME)

doc:
	doxygen Doxyfile

seeDoc:
	firefox doc/index.html

towerdefense: $(BUILD_DIR)/main.o $(BUILD_DIR)/Enemy.o $(BUILD_DIR)/Tower.o $(BUILD_DIR)/Tile.o $(BUILD_DIR)/GameState.o $(BUILD_DIR)/Spell.o $(BUILD_DIR)/BFS.o $(BUILD_DIR)/Coord.o $(BUILD_DIR)/FireTower.o $(BUILD_DIR)/IceTower.o $(BUILD_DIR)/SniperTower.o $(BUILD_DIR)/Minion.o $(BUILD_DIR)/Orc.o $(BUILD_DIR)/Dragon.o $(BUILD_DIR)/Boss.o $(BUILD_DIR)/Character.o $(BUILD_DIR)/Wall.o $(BUILD_DIR)/Path.o $(BUILD_DIR)/FreeTowerSpot.o $(BUILD_DIR)/Renderer.o $(BUILD_DIR)/TowerMenu.o $(BUILD_DIR)/SaveFileHandler.o $(BUILD_DIR)/GameStarter.o $(BUILD_DIR)/FireSpell.o $(BUILD_DIR)/IceSpell.o $(BUILD_DIR)/Targeting.o $(BUILD_DIR)/TargetingClosest.o $(BUILD_DIR)/TargetingFarthest.o $(BUILD_DIR)/TargetingStrongest.o $(BUILD_DIR)/Game.o $(BUILD_DIR)/GameUpdater.o
	$(LD) $(BUILD_DIR)/main.o $(BUILD_DIR)/Enemy.o $(BUILD_DIR)/Tower.o $(BUILD_DIR)/Tile.o $(BUILD_DIR)/GameState.o $(BUILD_DIR)/Spell.o $(BUILD_DIR)/BFS.o $(BUILD_DIR)/Coord.o $(BUILD_DIR)/FireTower.o $(BUILD_DIR)/IceTower.o $(BUILD_DIR)/SniperTower.o $(BUILD_DIR)/Minion.o $(BUILD_DIR)/Orc.o $(BUILD_DIR)/Dragon.o $(BUILD_DIR)/Boss.o $(BUILD_DIR)/Character.o $(BUILD_DIR)/Wall.o $(BUILD_DIR)/Path.o $(BUILD_DIR)/FreeTowerSpot.o $(BUILD_DIR)/Renderer.o $(BUILD_DIR)/TowerMenu.o $(BUILD_DIR)/SaveFileHandler.o $(BUILD_DIR)/GameStarter.o $(BUILD_DIR)/FireSpell.o $(BUILD_DIR)/IceSpell.o $(BUILD_DIR)/Targeting.o $(BUILD_DIR)/TargetingClosest.o $(BUILD_DIR)/TargetingFarthest.o $(BUILD_DIR)/TargetingStrongest.o $(BUILD_DIR)/Game.o $(BUILD_DIR)/GameUpdater.o -o $(BIN_NAME)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(BUILD_DIR)/Game.o $(BUILD_DIR)/GameState.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/Game.o: $(SRC_DIR)/Game.cpp $(SRC_DIR)/Game.h $(BUILD_DIR)/GameState.o $(BUILD_DIR)/Renderer.o $(BUILD_DIR)/TowerMenu.o $(BUILD_DIR)/SaveFileHandler.o $(BUILD_DIR)/GameStarter.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/Game.cpp -o $(BUILD_DIR)/Game.o

$(BUILD_DIR)/GameState.o: $(SRC_DIR)/GameState.cpp $(SRC_DIR)/GameState.h $(BUILD_DIR)/Tile.o $(BUILD_DIR)/Tower.o $(BUILD_DIR)/Enemy.o $(BUILD_DIR)/Coord.o $(SRC_DIR)/ConfigHolder.h
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/GameState.cpp -o $(BUILD_DIR)/GameState.o

$(BUILD_DIR)/Enemy.o: $(SRC_DIR)/Enemy.cpp $(SRC_DIR)/Enemy.h $(BUILD_DIR)/Tile.o $(BUILD_DIR)/Spell.o $(SRC_DIR)/ConfigHolder.h
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/Enemy.cpp -o $(BUILD_DIR)/Enemy.o

$(BUILD_DIR)/Minion.o: $(SRC_DIR)/Minion.cpp $(SRC_DIR)/Minion.h $(BUILD_DIR)/Enemy.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/Minion.cpp -o $(BUILD_DIR)/Minion.o

$(BUILD_DIR)/Orc.o: $(SRC_DIR)/Orc.cpp $(SRC_DIR)/Orc.h $(BUILD_DIR)/Enemy.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/Orc.cpp -o $(BUILD_DIR)/Orc.o

$(BUILD_DIR)/Dragon.o: $(SRC_DIR)/Dragon.cpp $(SRC_DIR)/Dragon.h $(BUILD_DIR)/Enemy.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/Dragon.cpp -o $(BUILD_DIR)/Dragon.o

$(BUILD_DIR)/Boss.o: $(SRC_DIR)/Boss.cpp $(SRC_DIR)/Boss.h $(BUILD_DIR)/Enemy.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/Boss.cpp -o $(BUILD_DIR)/Boss.o

$(BUILD_DIR)/Tower.o: $(SRC_DIR)/Tower.cpp $(SRC_DIR)/Tower.h $(BUILD_DIR)/Tile.o $(BUILD_DIR)/Enemy.o $(SRC_DIR)/ConfigHolder.h $(BUILD_DIR)/TargetingClosest.o $(BUILD_DIR)/TargetingFarthest.o $(BUILD_DIR)/TargetingStrongest.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/Tower.cpp -o $(BUILD_DIR)/Tower.o

$(BUILD_DIR)/FireTower.o: $(SRC_DIR)/FireTower.cpp $(SRC_DIR)/FireTower.h $(BUILD_DIR)/Tower.o $(BUILD_DIR)/FireSpell.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/FireTower.cpp -o $(BUILD_DIR)/FireTower.o

$(BUILD_DIR)/IceTower.o: $(SRC_DIR)/IceTower.cpp $(SRC_DIR)/IceTower.h $(BUILD_DIR)/Tower.o $(BUILD_DIR)/IceSpell.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/IceTower.cpp -o $(BUILD_DIR)/IceTower.o

$(BUILD_DIR)/SniperTower.o: $(SRC_DIR)/SniperTower.cpp $(SRC_DIR)/SniperTower.h $(BUILD_DIR)/Tower.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/SniperTower.cpp -o $(BUILD_DIR)/SniperTower.o

$(BUILD_DIR)/Tile.o: $(SRC_DIR)/Tile.cpp $(SRC_DIR)/Tile.h
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/Tile.cpp -o $(BUILD_DIR)/Tile.o

$(BUILD_DIR)/Character.o: $(SRC_DIR)/Character.cpp $(SRC_DIR)/Character.h $(BUILD_DIR)/Tile.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/Character.cpp -o $(BUILD_DIR)/Character.o

$(BUILD_DIR)/Wall.o: $(SRC_DIR)/Wall.cpp $(SRC_DIR)/Wall.h $(BUILD_DIR)/Tile.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/Wall.cpp -o $(BUILD_DIR)/Wall.o

$(BUILD_DIR)/Path.o: $(SRC_DIR)/Path.cpp $(SRC_DIR)/Path.h $(BUILD_DIR)/Tile.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/Path.cpp -o $(BUILD_DIR)/Path.o

$(BUILD_DIR)/FreeTowerSpot.o: $(SRC_DIR)/FreeTowerSpot.cpp $(SRC_DIR)/FreeTowerSpot.h $(BUILD_DIR)/Tile.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/FreeTowerSpot.cpp -o $(BUILD_DIR)/FreeTowerSpot.o

$(BUILD_DIR)/Spell.o: $(SRC_DIR)/Spell.cpp $(SRC_DIR)/Spell.h
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/Spell.cpp -o $(BUILD_DIR)/Spell.o

$(BUILD_DIR)/FireSpell.o: $(SRC_DIR)/FireSpell.cpp $(SRC_DIR)/FireSpell.h $(BUILD_DIR)/Spell.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/FireSpell.cpp -o $(BUILD_DIR)/FireSpell.o

$(BUILD_DIR)/IceSpell.o: $(SRC_DIR)/IceSpell.cpp $(SRC_DIR)/IceSpell.h $(BUILD_DIR)/Spell.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/IceSpell.cpp -o $(BUILD_DIR)/IceSpell.o

$(BUILD_DIR)/BFS.o: $(SRC_DIR)/BFS.cpp $(SRC_DIR)/BFS.h $(BUILD_DIR)/Tile.o $(BUILD_DIR)/Coord.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/BFS.cpp -o $(BUILD_DIR)/BFS.o

$(BUILD_DIR)/Coord.o: $(SRC_DIR)/Coord.cpp $(SRC_DIR)/Coord.h
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/Coord.cpp -o $(BUILD_DIR)/Coord.o

$(BUILD_DIR)/Renderer.o: $(SRC_DIR)/Renderer.cpp $(SRC_DIR)/Renderer.h $(BUILD_DIR)/GameState.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/Renderer.cpp -o $(BUILD_DIR)/Renderer.o

$(BUILD_DIR)/TowerMenu.o: $(SRC_DIR)/TowerMenu.cpp $(SRC_DIR)/TowerMenu.h $(BUILD_DIR)/Renderer.o $(BUILD_DIR)/Targeting.o $(BUILD_DIR)/FreeTowerSpot.o $(BUILD_DIR)/FireTower.o $(BUILD_DIR)/IceTower.o $(BUILD_DIR)/SniperTower.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/TowerMenu.cpp -o $(BUILD_DIR)/TowerMenu.o

$(BUILD_DIR)/SaveFileHandler.o: $(SRC_DIR)/SaveFileHandler.cpp $(SRC_DIR)/SaveFileHandler.h $(BUILD_DIR)/GameState.o $(BUILD_DIR)/IceTower.o $(BUILD_DIR)/SniperTower.o $(BUILD_DIR)/FireTower.o $(BUILD_DIR)/Minion.o $(BUILD_DIR)/Orc.o $(BUILD_DIR)/Dragon.o $(BUILD_DIR)/Boss.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/SaveFileHandler.cpp -o $(BUILD_DIR)/SaveFileHandler.o

$(BUILD_DIR)/GameStarter.o: $(SRC_DIR)/GameStarter.cpp $(SRC_DIR)/GameStarter.h $(BUILD_DIR)/GameState.o $(BUILD_DIR)/Path.o $(BUILD_DIR)/FreeTowerSpot.o $(BUILD_DIR)/Wall.o $(BUILD_DIR)/Character.o $(BUILD_DIR)/BFS.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/GameStarter.cpp -o $(BUILD_DIR)/GameStarter.o

$(BUILD_DIR)/Targeting.o: $(SRC_DIR)/Targeting.cpp $(SRC_DIR)/Targeting.h $(BUILD_DIR)/Enemy.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/Targeting.cpp -o $(BUILD_DIR)/Targeting.o

$(BUILD_DIR)/TargetingClosest.o: $(SRC_DIR)/TargetingClosest.cpp $(SRC_DIR)/TargetingClosest.h $(BUILD_DIR)/Targeting.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/TargetingClosest.cpp -o $(BUILD_DIR)/TargetingClosest.o

$(BUILD_DIR)/TargetingFarthest.o: $(SRC_DIR)/TargetingFarthest.cpp $(SRC_DIR)/TargetingFarthest.h $(BUILD_DIR)/Targeting.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/TargetingFarthest.cpp -o $(BUILD_DIR)/TargetingFarthest.o

$(BUILD_DIR)/TargetingStrongest.o: $(SRC_DIR)/TargetingStrongest.cpp $(SRC_DIR)/TargetingStrongest.h $(BUILD_DIR)/Targeting.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/TargetingStrongest.cpp -o $(BUILD_DIR)/TargetingStrongest.o

$(BUILD_DIR)/GameUpdater.o: $(SRC_DIR)/GameUpdater.cpp $(SRC_DIR)/GameUpdater.h $(BUILD_DIR)/GameState.o $(BUILD_DIR)/Minion.o $(BUILD_DIR)/Orc.o $(BUILD_DIR)/Dragon.o $(BUILD_DIR)/Boss.o $(BUILD_DIR)/Path.o
	$(CXX) $(CFLAGS) -c $(SRC_DIR)/GameUpdater.cpp -o $(BUILD_DIR)/GameUpdater.o


MakeBuild:
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(BUILD_DIR)/*.o $(BIN_NAME)
	rm -rf $(BUILD_DIR)
	rm -rf doc

cleanBuild:
	rm -rf $(BUILD_DIR)

