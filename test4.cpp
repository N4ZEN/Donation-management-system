// #include "stdafx.h" 
//#include "stdio.h"
#include "stdlib.h"
#include <conio.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

#pragma warning(disable:4996)

struct addDonation
{
	char productCode[20];
	char productName[20];
	char donator[20];
	int numberOfShipment;
	float quantityReceivedMillions;
};

struct addDistribution
{
	char productCode[20];
	char productName[20];
	char Hospital[50];
	float quantityReceivedMillions;
};

void viewAll(void);
void viewAllDist(void);
void createInventory(void);
void updateInvetory(void);
void searchDonation(void);
void Signup(void);
int Login(void);



 
int main()
{
	int choice;
	int cOption;


employeeOption:
	printf("\n\n========== Malaysia Red Crescent Society and a COVID-19 Donation Management System  ==========\n\n");


	printf("\n-1. Signup\n");
	printf("-2. Login\n");
	printf("-0.Exit\n");
	scanf("%d", &cOption);

	if (cOption == 1)
	{
		Signup();
		goto employeeOption;
	}
	else if (cOption == 2)
	{
		if (Login() == 1)
		{
			Choice:

				printf("\n========== Main Menu  ==========\n");

				printf("\n-1.Inventory Creation\n");
				printf("-2.Update Inventory\n");
				printf("-3.Search inventory\n");
				printf("-4.list All Donations\n");
				printf("-5. Log out\n");
				scanf("%d", &choice);

				switch (choice)
				{
				case 1:
					createInventory();
					goto Choice;
					break;
				case 2:
					updateInvetory();
					goto Choice;
					break;
				case 3:
					searchDonation();
					goto Choice;
					break;
				case 4:
					viewAll();
					viewAllDist();
					goto Choice;
					break;
				case 5:
					goto employeeOption;
					break;
				default:
					printf("\nIncorrect input, try again\n");
					cin.get();
					goto Choice;
					break;
				}
		}
		else
		{
			goto employeeOption;
		}
		
	}else if (cOption == 0)
	{
		system("exit");
		//break;
	} else {
		printf("\nIncorrect input, try again\n");
		cin.get();
		goto Choice;
		//break;
	}
//	break;

	system("pause");
}

//signup function
void Signup()
{
	char username[20], password[20];
	char scan[20];

	FILE *fp;
	fp = fopen("UserData.txt", "a+");

	if (fp == NULL)
	{
		printf("Cannot open file. \n");
		printf("No users have signed up. \n");
		return;
	}

	printf("\nEnter Username: \n");
	scanf("%s", username);

	printf("\nEnter Password: \n");
	scanf("%s", password);

	while (!feof(fp))
	{
		fscanf(fp, "%s", scan);

		if (strcmp(scan, username) == 0)
		{
			printf("\nUsername already exist. \n");
			printf("Please try a new username or login if you are already a user. \n");
			cin.get();
			break;
		}
	}

	if (strcmp(scan, username) != 0)
	{

		printf("\nUser added! \n");
		fprintf(fp, "\n%s\t", username);
		fprintf(fp, "%s", password);
		cin.get();
	}
	fclose(fp);
}

//login function
int Login()
{
	int result;
	char username[20], password[20];
	char inputUsername[20], inputPassword[20];

	FILE *fp;

	fp = fopen("UserData.txt", "r");

	if (fp == NULL)
	{
		printf("\nCannot open file. \n");
		printf("No login credentials found. Please Sign up first. \n");
		getche();
		std::cout << "\x1B[2J\x1B[H";

		result = 0;
		goto end;

	}

	printf("\nEnter Username: \n");
	scanf("%s", inputUsername);

	printf("\nEnter Password: \n");
	scanf("%s", inputPassword);

	if (strcmp(inputUsername, "Admin") == 0 && strcmp(inputPassword, "12345") == 0)
	{
		result = 2;
		printf("\nAdmin logged in Successfully\n");
		goto end;
	}

	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "%s", username);

			if (strcmp(inputUsername, username) == 0)
			{
				fscanf(fp, "%s", password);

				if (strcmp(inputPassword, password) != 0)
				{
					printf("Incorrect Password");
					result = 0;
					rewind(fp);
					break;
				}

				else
				{
					printf("\nSuccessfully Logged in! \n\n");
					result = 1;
					break;
				}
			}
		}
	}

	if (strcmp(inputUsername, username) != 0)
	{
		printf("\nIncorrect Username");
		result = 0;
		cin.get();
	}
end:
	return result;
}

//view all undistributed donations
void viewAll()
{
	struct addDonation Donation;
	char productCode[20];
	char productName[20];
	char donator[20];
	int numberOfShipment;
	float quantityReceivedMillions;

	FILE* fp;
	

	fp = fopen("Donations.txt", "r");

	if (fp == NULL)
	{
		printf("\nCannot open donations file. \n");
		printf("No Donations have been created yet. \n");
		goto ends;
		
	}

	printf("\n\n====== Displaying All Donations ========\n\n");

	while (!feof(fp))
	{
		fscanf(fp, "%s", &productCode);
		fscanf(fp, "%s", &productName);
		fscanf(fp, "%s", &donator);
		fscanf(fp, "%d", &numberOfShipment);
		fscanf(fp, "%f", &quantityReceivedMillions);

		printf("\nProduct Code: %s\n", productCode);
		printf("Product Name: %s \n", productName);
		printf("Donator: %s\n", donator);
		printf("Number Of Shipment: %d\n", numberOfShipment);
		printf("Quantity Received Millions: %.2f\n", quantityReceivedMillions);
	}
	fclose(fp);

	

	ends: 
	printf("\n");

}

//view all ditributed donations
void viewAllDist()
{
	struct addDistribution dis;
	char ProductCode[20];
	char ProductName[20];
	char Hospital[50];
	float quantityReceivedMillions;

	FILE* fp;

	fp = fopen("Dist.txt", "r");

	if (fp == NULL)
	{
		printf("\nCannot open distributions file. \n");
		printf("No Donation distributions have been created yet. \n");
		goto enddist;
		
	}

	printf("\n\n====== Displaying All Distributions ========\n\n");

	while (!feof(fp))
	{
		fscanf(fp, "%s", &ProductCode);
		fscanf(fp, "%s", &ProductName);
		fscanf(fp, "%s", &Hospital);
		fscanf(fp, "%f", &quantityReceivedMillions);

		printf("\nProduct Code: %s\n", ProductCode);
		printf("Product Name: %s \n", ProductName);
		printf("Hospital(s): %s\n", Hospital);
		printf("Quantity Received Millions: %.2f\n", quantityReceivedMillions);
	}
	fclose(fp);

	enddist: 
	printf("\n==> back to main menu \n");

}

// creates new inventory 
void createInventory()
{
	struct addDonation Donation;

	char inputCode[20];
	char productName[20];
	char productCode[20];
	char donator[20];
	int numberOfShipment;
	float quantityReceivedMillions;
//	char x[50], y[20], z[20];
	char a[20];

	int addnewOption;
	
	FILE *fp;

	std::ofstream outfile;

 outfile.open("Donations.txt", std::ios_base::app); // append instead of overwrite
  //return 0;

	fp = fopen("Donations.txt", "a+");

	if (fp == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

	while (!feof(fp))
	{

choose:

	printf("\n========== Add Inventory  ==========\n");

	printf("\nEnter Product Code: \n");
	
	scanf("%s", &productCode);

		// while ( fgets (a, 20, fp)!=NULL ) {
		// 	printf("int");
		
		// 		if (strcmp(a, productCode) == 0)
		// 	{
		// 		printf("\nProduct code already exists. Try again\n");
		// 		rewind(fp);
		// 		goto choose;
		// 		break;
		// 	}
		// 	//}
		// }

			fscanf(fp, "%s", &a);
			// fscanf(fp, "%s", &productCode);
			fscanf(fp, "%s", &productName);
			fscanf(fp, "%s", &donator);
			fscanf(fp, "%d", &numberOfShipment);
			fscanf(fp, "%f", &quantityReceivedMillions);

		if (strcmp(a, productCode) == 0)
		{
			printf("\nProduct code already exists. Try again\n");
			//rewind(fp);
			goto choose;
			//break;
		}
		else if (strcmp(productCode, a) != 0)
		{
			printf("\nEnter Product Name: \n");
			scanf("%s", &productName);
			printf("\nEnter the Donator: \n");
			scanf("%s", &donator);
			printf("\nEnter the number of Shipment: \n");
			scanf("%d", &numberOfShipment);
			printf("\nEnter the quantity recieved(in millions): \n");
			scanf("%f", &quantityReceivedMillions);

			printf("\n==> Donation item added successfully\n");

			printf("\nProduct Code: %s", productCode);
			printf("\nProduct Name: %s", productName);
			printf("\nDonator:  %s", donator);
			printf("\nNumber of Shipments: %d", numberOfShipment);
			printf("\nQuantity recieved (in millions): %.2f\n", quantityReceivedMillions);

			// outfile << "\n" << productCode << "\t" << numberOfShipment << "\t" << donator << "\t" << numberOfShipment << "\t" << quantityReceivedMillions << std::endl;


			fprintf(fp, "\n%s\t", productCode);
			fprintf(fp, "%s\t", productName);
			fprintf(fp, "%s\t", donator);
			fprintf(fp, "%d\t", numberOfShipment);
			fprintf(fp, "%.2f", quantityReceivedMillions); 

		AddnewInventory:

			printf("\n ** Do you want to add a another inventory item? \n");
			printf(" Press 1 for new Inventory Creation\n");
			printf(" Press 2 to go back to main menu \n");
			scanf("%d", &addnewOption);

			if (addnewOption == 1)
			{
				rewind(fp);
				fclose(fp);
				outfile.close();
				fp = fopen("Donations.txt", "a");

				goto choose;
				//break;
			}
			else if (addnewOption == 2)
			{
				//printf("\n==> back to main manu\n");
				fclose(fp);
				break;
			}
			else
			{
				printf("\nIncorrect Input. Try again.\n");
				goto AddnewInventory;
				break;
			}
			break;
			//cin.get();
		}
		break;

	}

	fclose(fp);
	printf("\n==> back to main menu \n");

}

//searches donations
void searchDonation()
{
	struct addDonation Donation;

	char productName[20];
	char productCode[23];
	char donator[20];
	char inputCode[20];
	int numberOfShipment;
	float quantityReceivedMillions;
	char x[50], z[10], a[10];
	int y;

	FILE* fp;

	fp = fopen("Donations.txt", "r");

	if (fp == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

start:
	while (!feof(fp))
	{

	printf("\nEnter the Product Code\n");
	scanf("%s", &inputCode);


		fscanf(fp, "%s", &productCode);

			fscanf(fp, "%s", &productName);
			fscanf(fp, "%s", &donator);
			fscanf(fp, "%d", &numberOfShipment);
			fscanf(fp, "%f", &quantityReceivedMillions);

		if (strcmp(productCode, inputCode) == 0)
		{
			printf("\nProduct Code: %s", productCode);
			printf("\nProduct Name: %s", productName);
			printf("\nDonator:  %s", donator);
			printf("\nDonator:  %d", numberOfShipment);
			printf("\nQuantity Recieved Millions: %.2f", quantityReceivedMillions);
			//getche();
			break;
		}
	
	

		else if (strcmp(productCode, inputCode)!= 0)
		{
			while (!feof(fp))
			{
				fscanf(fp, "%s", &productCode);

					fscanf(fp, "%s", &productName);
					fscanf(fp, "%s", &donator);
					fscanf(fp, "%d", &numberOfShipment);
					fscanf(fp, "%f", &quantityReceivedMillions);

				if (strcmp(productCode, inputCode) == 0)
				{
					printf("\nProduct Code: %s", productCode);
					printf("\nProduct Name: %s", productName);
					printf("\nDonator:  %s", donator);
					printf("\nDonator:  %d", numberOfShipment);
					printf("\nQuantity Recieved Millions: %.2f", quantityReceivedMillions);
					//getche();
					goto exits;
					break;
				}
			}
	
		search:
			printf("\nIncorrect product Code, press 1 to try again\n");
			printf("\nPress 2 to go back to main menu.\n");
			scanf("%d", &y);

			if (y == 1)
			{
				
				rewind(fp);
				goto start;
				break;
			}
			else if (y == 2)
			{
				// printf("\n==> back to main manu\n");
				break;
			}
			else
			{
				printf("\nIncorrect Input. Try again.\n");
				goto start;
				break;
			}


			//getche();
		}
	}
exits:
	fclose(fp);
	printf("\n\n==> back to main manu\n");

}

// updated inventory
void updateInvetory()
{
	struct addDonation Donation1;
	struct addDonation Donation2;
	struct addDistribution Distribution1;
	struct addDistribution Distribution2;

	//struct addDistribution Distribution1;
	//struct addDistribution Distribution2;

	char inputCode[20];
//	float newQuantity;
	float inputquantity;
	int updatechoice;
	//char productName[20];
	// char productCode[20];
	// char donator[20];
	// int numberOfShipment;
	// float quantityReceivedMillions;
	char z[10], a[10];
	int y;


	FILE* fp, * fp2, * fp3, * fp4;

	fp = fopen("Donations.txt", "r");

	if (fp == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

	fp2 = fopen("temp.txt", "a+");

	if (fp2 == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

	fp3 = fopen("Dist.txt", "a+");

	if (fp3 == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

	fp4 = fopen("temp2.txt", "a+");

	if (fp4 == NULL)
	{
		printf("Cannot open file. \n");
		printf("Program stopped. \n");
		system("close");
	}

	

updatechoices:
		printf("\n1. Update Donation Quantity.");
		printf("\n2. Update Distribution Quantity.\n");
		scanf("%d", &updatechoice);

		
	if (updatechoice == 1){
		viewAll();
update:
	while (!feof(fp))
	{

	printf("\n ===> Enter the Product Code to update Donation: \n");
		scanf("%s", &inputCode);

		fscanf(fp, "%s", &Donation1.productCode);
			fscanf(fp, "%s", &Donation1.productName);
			fscanf(fp, "%s", &Donation1.donator);
			fscanf(fp, "%d", &Donation1.numberOfShipment);
			fscanf(fp, "%f", &Donation1.quantityReceivedMillions);

		if (strcmp(inputCode, Donation1.productCode) == 0)
		{
			// fscanf(fp, "%s", &Donation1.productCod2e);
			found:
			printf("\nDonation Found\n");

			printf("\nEnter the new quantity recieved: \n");
			scanf("%f", &inputquantity);

			float newQuantity = Donation1.quantityReceivedMillions + inputquantity;

			printf("\nDonation Updated\n");

			fprintf(fp2, "\n%s\t", Donation1.productCode);
			fprintf(fp2, "%s\t", Donation1.productName);
			fprintf(fp2, "%s\t", Donation1.donator);
			fprintf(fp2, "%d\t", Donation1.numberOfShipment);
			fprintf(fp2, "%.2f", newQuantity);

			rewind(fp);

			while (!feof(fp))
			{
				fscanf(fp, "%s", &Donation2.productCode);
				fscanf(fp, "%s", &Donation2.productName);
				fscanf(fp, "%s", &Donation2.donator);
				fscanf(fp, "%d", &Donation2.numberOfShipment);
				fscanf(fp, "%f", &Donation2.quantityReceivedMillions);

				if (strcmp(Donation1.productCode, Donation2.productCode) != 0)
				{
					fprintf(fp2, "\n%s\t", Donation2.productCode);
					fprintf(fp2, "%s\t", Donation2.productName);
					fprintf(fp2, "%s\t", Donation2.donator);
					fprintf(fp2, "%d\t", Donation2.numberOfShipment);
					fprintf(fp2, "%.2f", Donation2.quantityReceivedMillions);
				}

				  //  break;
			}
			goto closes;
			break;
		}
		else if (strcmp(inputCode, Donation1.productCode) != 0)
		{
			while (!feof(fp))
			{
				fscanf(fp, "%s", &Donation1.productCode);

					fscanf(fp, "%s", &Donation1.productName);
					fscanf(fp, "%s", &Donation1.donator);
					fscanf(fp, "%d", &Donation1.numberOfShipment);
					fscanf(fp, "%f", &Donation1.quantityReceivedMillions);

				if (strcmp(Donation1.productCode, inputCode) == 0)
				{
					
					goto found;
					break;
				}
			}
		redoupdate:
			printf("\nDonation not found, press 1 to try again\n");
			printf("\nPress 2 to go back to main menu.\n");
			scanf("%d", &y);

			if (y == 1)
			{
				rewind(fp);
				//rewind(fp3);
				goto update;
				break;
			}
			else if (y == 2)
			{
			//	rewind(fp);
				//rewind(fp3);
				fclose(fp);
				fclose(fp2);
				fclose(fp3);
				fclose(fp4);
				remove("temp.txt");
				remove("temp2.txt");
				goto exit;
				break;
			}
			else
			{
				printf("\nIncorrect Input. Try again.\n");
				goto redoupdate;
				break;
			}
			break;
		}
	}

	closes:
	fclose(fp);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);

	remove("Donations.txt");
	rename("temp.txt", "Donations.txt");
	remove("temp2.txt");
	goto exit;

	} else if (updatechoice == 2)
	{
		while (!feof(fp))
		{

	viewAll();
	
	updateDist:

	printf("\n ===> Enter the Product Code to update Distributions: \n");
	scanf("%s", &inputCode);

		fscanf(fp, "%s", &Donation1.productCode);

			fscanf(fp, "%s", &Donation1.productName);
			fscanf(fp, "%s", &Donation1.donator);
			fscanf(fp, "%d", &Donation1.numberOfShipment);
			fscanf(fp, "%f", &Donation1.quantityReceivedMillions);

		if (strcmp(inputCode, Donation1.productCode) == 0)
		{
			// fscanf(fp, "%s", &Donation1.productCode);
		founddist:
			printf("\nProduct Found\n");

			printf("\nEnter the quantity you want to distribute: \n");
			scanf("%f", &inputquantity);

			if(inputquantity > Donation1.quantityReceivedMillions) {
				printf("Distribution quantity is higher than Donation quantity.");
				goto updateDist;
				break;
			}

			float newQuantity = Donation1.quantityReceivedMillions - inputquantity;

			printf("\nDonation Updated\n");

			fprintf(fp2, "\n%s\t", Donation1.productCode);
			fprintf(fp2, "%s\t", Donation1.productName);
			fprintf(fp2, "%s\t", Donation1.donator);
			fprintf(fp2, "%d\t", Donation1.numberOfShipment);
			fprintf(fp2, "%.2f", newQuantity);

			rewind(fp);



			while (!feof(fp))
			{
				fscanf(fp, "%s", &Donation2.productCode);
				fscanf(fp, "%s", &Donation2.productName);
				fscanf(fp, "%s", &Donation2.donator);
				fscanf(fp, "%d", &Donation2.numberOfShipment);
				fscanf(fp, "%f", &Donation2.quantityReceivedMillions);

				if (strcmp(inputCode, Donation2.productCode) != 0)
				{
					fprintf(fp2, "\n%s\t", Donation2.productCode);
					fprintf(fp2, "%s\t", Donation2.productName);
					fprintf(fp2, "%s\t", Donation2.donator);
					fprintf(fp2, "%d\t", Donation2.numberOfShipment);
					fprintf(fp2, "%.2f", Donation2.quantityReceivedMillions);
				}
			}

			// while (!feof(fp3))
			// {
				
					fscanf(fp3, "%s", &Distribution1.productCode);
					fscanf(fp3, "%s", &Distribution1.productName);
					fscanf(fp3, "%s", &Distribution1.Hospital);
					fscanf(fp3, "%f", &Distribution1.quantityReceivedMillions);

				if(strcmp(Distribution1.productCode, inputCode) == 0) {

					float newDistQuantity = Distribution1.quantityReceivedMillions + inputquantity;

					printf("\n Distribution Updated\n");



					fprintf(fp4, "\n%s\t", Distribution1.productCode);
					fprintf(fp4, "%s\t", Distribution1.productName);
					fprintf(fp4, "%s\t", Distribution1.Hospital);
					fprintf(fp4, "%.2f", newDistQuantity);

					rewind(fp3);
					rewind(fp4);

					while (!feof(fp3))
					{
						fscanf(fp3, "%s", &Distribution2.productCode);
						fscanf(fp3, "%s", &Distribution2.productName);
						fscanf(fp3, "%s", &Distribution2.Hospital);
						fscanf(fp3, "%f", &Distribution2.quantityReceivedMillions);

						if (strcmp(inputCode, Distribution2.productCode) != 0)
						{
							fprintf(fp4, "\n%s\t", Distribution2.productCode);
							fprintf(fp4, "%s\t", Distribution2.productName);
							fprintf(fp4, "%s\t", Distribution2.Hospital);
							fprintf(fp4, "%.2f", Distribution2.quantityReceivedMillions);
						}
					}


				} else if (strcmp(Distribution1.productCode, inputCode) != 0) {
					char Hospital[50];
					printf("\nPlease enter Hospital(s) \n");
					scanf("%s", &Hospital);


					fprintf(fp4, "\n%s\t", inputCode);
					fprintf(fp4, "%s\t", Donation1.productName);
					fprintf(fp4, "%s\t", Hospital);
					fprintf(fp4, "%.2f", inputquantity);

					rewind(fp3);

					while (!feof(fp3))
					{
						// if (Distribution1.productCode != NULL)
						// {
						fscanf(fp3, "%s", &Distribution2.productCode);
						fscanf(fp3, "%s", &Distribution2.productName);
						fscanf(fp3, "%s", &Distribution2.Hospital);
						fscanf(fp3, "%f", &Distribution2.quantityReceivedMillions);

							if (strcmp(inputCode, Distribution2.productCode) != 0)
							{

							fprintf(fp4, "\n%s\t", Distribution2.productCode);
							fprintf(fp4, "%s\t", Distribution2.productName);
							fprintf(fp4, "%s\t", Distribution2.Hospital);
							fprintf(fp4, "%.2f", Distribution2.quantityReceivedMillions);
							//printf("b");
							}

						//}
					}
				}
			//}

			
			break;
		}
		else if (strcmp(inputCode, Donation1.productCode) != 0)
		{
			while (!feof(fp))
			{
				fscanf(fp, "%s", &Donation1.productCode);
				fscanf(fp, "%s", &Donation1.productName);
				fscanf(fp, "%s", &Donation1.donator);
				fscanf(fp, "%d", &Donation1.numberOfShipment);
				fscanf(fp, "%f", &Donation1.quantityReceivedMillions);

				if (strcmp(Donation1.productCode, inputCode) == 0)
				{
					
					goto founddist;
					break;
				}
			}
			
			redoupdateDist:

			printf("\nDonation not found, press 1 to try again\n");
			printf("\nPress 2 to go back to main menu.\n");
			scanf("%d", &y);

			if (y == 1)
			{

				goto updateDist;
				break;
			}
			else if (y == 2)
			{
				fclose(fp);
				fclose(fp2);
				fclose(fp3);
				fclose(fp4);
				remove("temp1.txt");
				remove("temp2.txt");
				goto exit;
				break;
			}
			else
			{
				printf("\nIncorrect Input. Try again.\n");
				goto redoupdateDist;
				break;
			}
			
		}
	}


	fclose(fp);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);

	remove("Donations.txt");
	rename("temp.txt", "Donations.txt");
	remove("Dist.txt");
	rename("temp2.txt", "Dist.txt");
	} else {
		// printf('incorrect Input. Please try again!');
		goto updatechoices;
	}

	exit: 
	printf("\n==> back to main manu\n");


}



