#include <vtkAxis.h>
#include <vtkChartXY.h>
#include <vtkContextScene.h>
#include <vtkContextView.h>
#include <vtkFloatArray.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPen.h>
#include <vtkPlot.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTable.h>
#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkRenderingContextOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

int main(int, char* [])
{

    vtkNew<vtkNamedColors> colors;

    // Create a table with some points in it.
    vtkNew<vtkTable> table;

    vtkNew<vtkFloatArray> arrX;
    arrX->SetName("X");
    table->AddColumn(arrX);

    vtkNew<vtkFloatArray> arrS;
    arrS->SetName("Sine");
    table->AddColumn(arrS);

    // Fill in the table with some example values.
    int numPoints = 69;
    float inc = 6.28 / (numPoints - 1);
    table->SetNumberOfRows(numPoints);
    for (int i = 0; i < numPoints; ++i)
    {
        table->SetValue(i, 0, i * inc);
        table->SetValue(i, 1, sin(i * inc));
    }

    // Set up the view
    vtkNew<vtkContextView> view;
    view->GetRenderWindow()->SetWindowName("VTK");
    view->GetRenderer()->SetBackground(colors->GetColor3d("White").GetData());
    vtkSmartPointer<vtkChartXY> chart = vtkSmartPointer<vtkChartXY>::New();
    vtkAxis* yAxis = chart->GetAxis(vtkAxis::LEFT);
    yAxis->SetTitle("Sine(x)");
    //vtkSmartPointer<vtkChartXY> chart = vtkSmartPointer<vtkChartXY>::New();
    vtkAxis* xAxis = chart->GetAxis(vtkAxis::BOTTOM);
    xAxis->SetTitle("X");

    // Add multiple line plots, setting the colors etc.
    //vtkNew<vtkChartXY> chart;
    view->GetScene()->AddItem(chart);
    vtkPlot* line = chart->AddPlot(vtkChart::LINE);
    line->SetInputData(table, 0, 1);
    line->SetColor(0, 0, 0, 255);
    line->SetWidth(3.5);


    // For dotted line, the line type can be from 2 to 5 for different dash/dot
    // patterns (see enum in vtkPen containing DASH_LINE, value 2):
    // #ifndef WIN32
    //   line->GetPen()->SetLineType(vtkPen::DASH_LINE);
    // #endif
    // (ifdef-ed out on Windows because DASH_LINE does not work on Windows
    //  machines with built-in Intel HD graphics card...)

    // view->GetRenderWindow()->SetMultiSamples(0);

    // Start interactor
    view->GetRenderWindow()->Render();
    view->GetInteractor()->Initialize();
    view->GetInteractor()->Start();

    return EXIT_SUCCESS;
}
