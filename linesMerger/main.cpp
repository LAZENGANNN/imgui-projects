#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <filesystem>
#include <cmath>
#include <format>

struct Line {
	double x1;
	double y1;
	double x2;
	double y2;

	Line(){};

	Line(double x1, double y1, double x2, double y2) {
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}

};

bool doubleComapre(double p1, double p2){
	// double a = 0.0001;
	// return (abs(p1-p2) < (pow(10,-9)));
	return (fabs(p1-p2) < 0.000000001);
}

void printLines(std::vector<Line> testvec) {
	printf("\n");
	for (const auto& l : testvec) {
		printf("(%.0lf;%.0lf)--(%.0lf;%.0lf)\n", l.x1, l.y1, l.x2, l.y2);
	}
}

void readFile(std::vector<Line>& lines, std::string fileName) {
	std::string singleLine;

	std::ifstream file;
	std::string path = "data/" + fileName;
	file.open(path);

	/*int fourCounter = 1;*/

	double x1;
	double y1;
	double x2;
	double y2;

	while (file >> x1 >> y1 >> x2 >> y2) {
		
		//std::cout << x1 <<y1 << x2 << y2 <<std::endl;
		lines.push_back(Line(x1, y1, x2, y2));
	}
	file.close();
}

int isOneLine(Line & l1, Line& l2) {
	int mergetype = 0;

	bool sameStartEnd = 0;
	bool sameLine = 0;

	double vec1x = l1.x2 - l1.x1, vec1y = l1.y2 - l1.y1;
	double vec2x = l2.x2 - l2.x1, vec2y = l2.y2 - l2.y1;

	if (!(vec1x * vec2y == vec1y * vec2x)) return 0;//(не) лежат на одной линии (коллиенарность)

	if (doubleComapre(l1.x2, l2.x1) && doubleComapre(l1.y2, l2.y1)) {
		mergetype = 1;
	}
	else if (doubleComapre(l1.x1, l2.x2) && doubleComapre(l1.y1, l2.y2)) {
		mergetype = 2;
	}
	else if (doubleComapre(l1.x1, l2.x1) && doubleComapre(l1.y1, l2.y1)) {
		mergetype = 3;
	}
	else if (doubleComapre(l1.x2, l2.x2) && doubleComapre(l1.y2, l2.y2)) {
		mergetype = 4;
	}

	//if ((l1.x2 == l2.x1 && l1.y2 == l2.y1)
	//	|| (l1.x1 == l2.x2 && l1.y1 == l2.y2)
	//	|| (l1.x1 == l2.x1 && l1.y1 == l2.y1)
	//	|| (l1.x2 == l2.x2 && l1.y2 == l2.y2)) { //начало/конец совпадают
	//	sameStartEnd = 1;
	//}

	//if (vec1x * vec2y == vec1y * vec2x) {  //лежат на одной линии (один угол наклона)
	//	sameLine = 1;
	//}

	//std::cout << std::endl <<"===is one line====\n" << sameStartEnd << "\t" << sameLine << "\t" << mergetype << std::endl;
	//return (sameStartEnd && sameLine) ? true : false;

	return mergetype;

}


void mergeLines(std::vector<Line>& lines/*, std::vector<Line>& newVectorLines*/) {
	int CurrentLineIndex = 0;
	bool merged = 0;
	
	do{
		if (lines.size() <= 1) break;
		merged = 0;
		Line line1 = lines[CurrentLineIndex];

		/*for (Line l : lines) {*/
		for (int i = 0; i < lines.size(); i++) {
			if (CurrentLineIndex == i) continue;
			Line line2 = lines[i];
			Line newLine;
			//printf("compare: (%.0lf;%.0lf)-(%.0lf;%.0lf) | (%.0lf;%.0lf)-(%.0lf;%.0lf)\n", 
			//	line1.x1, line1.y1, line1.x2, line1.y2, 
			//	line2.x1, line2.y1, line2.x2, line2.y2);

			switch (isOneLine(line1, line2)) {
			case 1: {
				newLine = { line1.x1, line1.y1, line2.x2, line2.y2 };
				merged = 1;
				break;
			}
			case 2: {  //(l1.x1 == l2.x2 && l1.y1 == l2.y2)
				newLine = { line2.x1, line2.y1, line1.x2, line1.y2 };
				merged = 1;

				break;
			}
			case 3: { //(l1.x1 == l2.x1 && l1.y1 == l2.y1)
				newLine = { line1.x2, line1.y2, line2.x2, line2.y2 };
				if (newLine.x1 == newLine.x2 && newLine.y1 == newLine.y2) {
					newLine = lines[i];
				}
				merged = 1;

				break;
			}
			case 4: { //(l1.x2 == l2.x2 && l1.y2 == l2.y2)
				newLine = { line2.x1, line2.y1, line1.x1, line1.y1 };
				if (newLine.x1 == newLine.x2 && newLine.y1 == newLine.y2) {
					newLine = lines[i];
				}
				merged = 1;

				break;
			}
			default: {
				//CurrentLineIndex++;  ????????????????????????????????????????????????
				continue;
				break;
			}
			}
			//std::cout << "\n" << merged;
			//printf("result: (%.0lf;%.0lf)-(%.0lf;%.0lf)\n\n", newLine.x1, newLine.y1, newLine.x2, newLine.y2);
			//printLines(lines);
			
			/*if (changes == 1) break;*/

			if (merged) {

				if (i > CurrentLineIndex) {
					Line buff = lines[lines.size() - 1];
					lines[lines.size() - 1] = lines[i];
					lines[i] = buff;
					lines.pop_back();


					buff = lines[lines.size() - 1];
					lines[lines.size() - 1] = lines[CurrentLineIndex];
					lines[CurrentLineIndex] = buff;
					lines.pop_back();

				}
				//else {
				//	Line buff = lines[lines.size() - 1];
				//	lines[lines.size() - 1] = lines[CurrentLineIndex];
				//	lines[CurrentLineIndex] = buff;
				//	lines.pop_back();

				//	buff = lines[lines.size() - 1];
				//	lines[lines.size() - 1] = lines[i];
				//	lines[i] = buff;
				//	lines.pop_back();

				//}
				lines.push_back(newLine);
				//CurrentLineIndex = 0;
				break;
			}
			
		}
		if(merged == 0) CurrentLineIndex++;
	 // while (merged == 1 || CurrentLineIndex < lines.size() - 1);
	 }	while (CurrentLineIndex < lines.size() - 1);
		
}


int main() {
    std::filesystem::create_directories("./result");

std::vector<std::string> files = {
		"01_basic_vertical.txt",
		"02_basic_horizontal_reversed.txt",
		"03_diagonals_all_orientations.txt",
		"03_diagonals_all_orientations.txt",
		"04_three_into_one.txt",
		"05_three_into_two.txt",
		"06_bend_in_the_middle.txt",
		"07_near_collinear_0.0002deg.txt",
		"08_tiny_segments.txt",
		"09_close_but_not_same_points.txt",
		"10_fold_back_and_overlap.txt",
		"11_gap_on_same_line.txt",
		"12_junctions.txt",
		"13_stars_and_crossings.txt",
		"14_zigzag_and_staircase.txt",
		"15_closed_shapes.txt",
		"16_long_chains.txt",
		"17_number_formats.txt",
		"18_angle_wrap_around.txt",
		"19_large_coordinates.txt",
		"20_single_segment.txt",
		"21_empty.txt",
		"22_big_mixed_100.txt",
		"23_stress_10000.txt"
};

for (const auto& f : files) {
	std::vector<Line> testvec = std::vector<Line>();

	readFile(testvec, f);

	//printLines(testvec);
	//for (const auto& l : testvec) {
	//	printf("(%.15lf;%.15lf) -- (%.15lf;%.15lf)\n", l.x1, l.y1, l.x2, l.y2);
	//}

	mergeLines(testvec);
	// std::cout << "===================================\n";
	//for (const auto& l : testvec) {
	//	printf("(%.15lf;%.15lf) -- (%.15lf;%.15lf)\n", l.x1, l.y1, l.x2, l.y2);
	//}

	std::string path = "result/" + f;
	std::fstream outFile(path, std::ios::out | std::ios::trunc);

	if (!outFile.is_open()) {
		std::cout << "out file error\n";
		return 0;
	}

		const auto digits = std::numeric_limits<double>::digits10;

	for (const auto& l : testvec) {
		//printf("(%.15lf;%.15lf) -- (%.15lf;%.15lf)\n", l.x1, l.y1, l.x2, l.y2);
		outFile 
		 << std::setprecision(17) << l.x1 << " "
		 << std::setprecision(17) << l.y1 << " "
		 << std::setprecision(17) << l.x2 << " " 
		 << std::setprecision(17) << l.y2 << std::endl;
		 
		 
		// outFile << l.x1 << " " << l.y1 << " " << l.x2 << " " << l.y2 << std::endl;

		//outFile 
		//  << std::format("{:f}", l.x1) << l.x1 << " "
		//  << std::format("{:f}", l.y1)<< l.y1 << " "
		//  << std::format("{:f}", l.x2) << l.x2 << " " 
		//  << std::format("{:f}", l.y2) << l.y2 << std::endl;
	}



	outFile.close();

}
}
