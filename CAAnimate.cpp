#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"

emp::web::Document doc{"target"};

class CAAnimator : public emp::web::Animate {

    const int num_h_boxes = 10;
    const int num_w_boxes = 15;
    const double RECT_SIDE = 25;
    const double width{num_w_boxes * RECT_SIDE};
    const double height{num_h_boxes * RECT_SIDE};


    //2D vectors to hold information about the current and next state of cells
    std::vector<std::vector<int> > cells;
    std::vector<std::vector<int>> next_cells;
    std::vector<std::vector<double>> fade_grid;

            

    // Canvas to draw on
    emp::web::Canvas canvas{width, height, "canvas"};


public:

    /**
     * @brief Constructor sets up canvas and initial glider pattern.
     */

    CAAnimator() {
        doc << canvas;
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");

        cells.resize(num_w_boxes, std::vector<int>(num_h_boxes, 0));
        next_cells.resize(num_w_boxes, std::vector<int>(num_h_boxes, 0));
        fade_grid.resize(num_w_boxes, std::vector<double>(num_h_boxes, 0.0));


        //Add an initial glider pattern
         AddGlider(1, 1);

    }

    /**
     * @brief Places a glider pattern at the given offset.
     * @param x_offset X offset for the pattern
     * @param y_offset Y offset for the pattern
     */
    void AddGlider(int x_offset, int y_offset) {
        cells[(x_offset + 1) % num_w_boxes][(y_offset + 0) % num_h_boxes] = 1;
        cells[(x_offset + 2) % num_w_boxes][(y_offset + 1) % num_h_boxes] = 1;
        cells[(x_offset + 0) % num_w_boxes][(y_offset + 2) % num_h_boxes] = 1;
        cells[(x_offset + 1) % num_w_boxes][(y_offset + 2) % num_h_boxes] = 1;
        cells[(x_offset + 2) % num_w_boxes][(y_offset + 2) % num_h_boxes] = 1;
    }

    /**
     * @brief Counts alive neighbors with toroidal wrapping.
     */
    int GetNeighborValue(int x, int y) {
        int count = 0;
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue; 
                int nx = (x + dx + num_w_boxes) % num_w_boxes;
                int ny = (y + dy + num_h_boxes) % num_h_boxes;
                count += cells[nx][ny];
            }
        }
        return count;
    }

    /**
     * @brief Updates the cell grid using Game of Life rules and smooth transitions.
     */
    void UpdateCells() {
        for (int x = 0; x < num_w_boxes; ++x) {
            for (int y = 0; y < num_h_boxes; ++y) {
                int neighbors = GetNeighborValue(x, y);
                if (cells[x][y] > 0.5) {
                    // If the cell is alive, fade toward white (1.0)
                    fade_grid[x][y] = std::min(fade_grid[x][y] + 0.1, 1.0);
                } else {
                    // If the cell is dead, fade toward black (0.0)
                    fade_grid[x][y] = std::max(fade_grid[x][y] - 0.05, 0.0);
                }

                // Live cell rules
                if (cells[x][y] == 1) {
                    next_cells[x][y] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
                } else {
                    // Dead cell becomes alive if exactly 3 neighbors are alive
                    next_cells[x][y] = (neighbors == 3) ? 1 : 0;
                }
            }
        }

        // Swap next state into current state
        cells = next_cells;
    }

    /*
    * Draw and update the CA each frame.
    */
    void DoFrame() override {
        canvas.Clear();

        // Draw each cell on the canvas
        for (int x = 0; x < num_w_boxes; x++){
             for (int y = 0; y < num_h_boxes; y++) {
                if (cells[x][y] > 0.5) {
                    // Red for active (glider) cells
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, emp::ColorRGB(255, 0, 0), "black");
                } else {
                    // Greyscale for fading background
                    double val = fade_grid[x][y];
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, emp::ColorHSV(0, 0, val), "black");
                }

            }
        }

       // Update cells for the next frame
        UpdateCells();
    }
};


// Create an instance of the animator
CAAnimator animator;


/*
* Have animator call DoFrame once to start
*/
int main() {
    animator.Step();
}

