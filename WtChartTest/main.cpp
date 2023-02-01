#include <Wt/WApplication.h>
#include <Wt/Chart/WCartesianChart.h>
#include <Wt/Chart/WAbstractChartModel.h>
#include <Wt/Chart/WAxis.h>

using namespace Wt;

struct Data
{
    int x;
    int y;
};

class Model : public Chart::WAbstractChartModel
{
public:
    std::vector<Data> _data;

    Model(const std::vector<Data>& data) :
        _data(data)
    {
        
    }

    virtual double data(int row, int column) const override
    {
        if(column == 0)
            return _data[row].x;
        if(column == 1)
            return _data[row].y;
        return -1;
    }

    virtual int columnCount() const override
    {
        return 2;
    }

    virtual int rowCount() const override
    {
        return _data.size();
    }
};

class HelloApplication : public WApplication
{
public:
    HelloApplication(const WEnvironment &env) : WApplication(env)
    {
        srand(time(nullptr));
        std::vector<Data> data;
        for(auto i = 0; i < 100; ++i)
            data.push_back({ i, rand() % 100 });

        auto  model = std::make_shared<Model>(data);

        auto chart = root()->addWidget(std::make_unique<Chart::WCartesianChart>());
        chart->resize(600, 400);
        chart->setModel(model);
        chart->setXSeriesColumn(0);
        chart->setType(Chart::ChartType::Scatter);
        auto series = std::make_unique<Chart::WDataSeries>(1, Chart::SeriesType::Curve, Chart::Axis::Y);
        series->setPen(Wt::WPen(WColor(0, 0, 255, 255)));
        series->setShadow(Wt::WShadow(3, 3, WColor(0, 0, 0, 127), 3));
        chart->addSeries(std::move(series));
    }
};

int main(int argc, char **argv)
{
    return WRun(argc, argv, [](const WEnvironment &env)
    {
        return std::make_unique<HelloApplication>(env);
    });
}