#include<bits/stdc++.h>
using namespace std;

float findMod(float a, float b){
    float mod; 
    if (a < 0) 
        mod = -a; 
    else
        mod =  a; 

    if (b < 0){
		b = -b; 
	}
    while (mod >= b) 
        mod = mod - b; 
  
    if (a < 0) 
        return -mod; 
  
    return mod; 
}

double Rand_float(double low, double high) {
	random_device rd;  
    mt19937 gen(rd()); 
    uniform_real_distribution<> dis(low, high);
    return dis(gen);
}

vector<float> add(vector<float> vector1, vector<float> vector2) {
	vector<float> output(vector1.size());

	for(int i = 0; i < vector1.size(); i++) {
		output[i] = vector1[i] + vector2[i];
	}

	return output;
}


vector<vector<float>> dot(vector<vector<float>> &input, vector<vector<float>> &weight){
	vector<vector<float>> res(input.size(), vector<float>(weight[0].size()));
	for(int i=0;i<input.size();i++){
		for(int j=0;j<weight[0].size();j++){
			for(int k=0;k<input[0].size();k++){
				res[i][j] += input[i][k]*weight[k][j];
			}
		}
	}
	return res;
}


class Dense{
	private:
		vector<vector<float>> output;
		vector<vector<float>> weights;
		vector<float> bias;
	public:
		Dense(int n_inputs, int n_neurons){
			weights = vector<vector<float>>(n_inputs, vector<float>(n_neurons));
			for(int i=0;i<n_inputs;i++){
				for(int j=0;j<n_neurons;j++){
					weights[i][j] = 0.1 * Rand_float(-1, 1);
				}
			}
			bias = vector<float>(n_neurons, 0);
		}
		void forward(vector<vector<float>> inputs){
			output = dot(inputs, weights);
			for(int i = 0; i < output.size(); i++) {
				output[i] = add(output[i], bias);
			}
		}
		void printOutput(){
			for(int i = 0; i < output.size(); i++) {
				for(int j = 0; j < output[0].size(); j++) {
					cout<<output[i][j]<<" ";
				}
				cout<<endl;
			}
		}
		vector<vector<float>> getOutput(){
			return output;
		}
};

class ReLU_Activation{
	private:
		vector<vector<float>> output;
	public:
		ReLU_Activation(vector<vector<float>> inputs){
			vector<vector<float>> output(inputs.size(), vector<float>(inputs[0].size()));
			for(int i=0;i<inputs.size();i++){
				for(int j=0;j<inputs[0].size();j++){
					if(inputs[i][j]>0){
						output[i][j] = inputs[i][j];
					}
					else{
						output[i][j] = 0.0;
					}
				}
			}
		}
};

int main(){
	vector<vector<float>> X = {{1, 2, 3, 2.5},
     				   {2.0, 5.0, -1.0, 2.0},
     				   {-1.5, 2.7, 3.3, -0.8}};

	Dense layer1(4,5);
	Dense layer2(5,2);
	ReLU_Activation activation1(X);
	cout << "First layer forward pass output:" << endl;
 	layer1.forward(X);
 	layer1.printOutput();

 	cout << endl << "Second layer forward pass output:" << endl;
 	layer2.forward(layer1.getOutput());
 	layer2.printOutput();
}
