/** @file Q1.c
 * @brief Solution of Question 1 of LA3.
 *
 * @author Shashank
 *
 * @date 8/21/2019
 */

#include<stdio.h>
#include<string.h>

char findClassOfIP(char str[]) {
	// storing first octet in arr[] variable
	char arr[4];
	int i = 0;
	while (str[i] != '.') {
		arr[i] = str[i];
		i++;
	}

	i--;
	int ip = 0, j = 1;
	while (i >= 0) {
		// converting str[] variable into number for comparison
		ip = ip + (str[i] - '0') * j;
		j = j * 10;
		i--;
	}

	if (ip >=1 && ip <= 126) {
		return 'A';
	}else if (ip >= 128 && ip <= 191) {
		return 'B';
	}else if (ip >= 192 && ip <= 223) {
		return 'C';
	}else if (ip >= 224 && ip <= 239) {
		return 'D';
	}else {
		return 'E';
	}
}

// Function to separate Network ID as well as Host ID and print them
void separateID(char str[], char ipClass) {
	// Initializing netID and host array to NULL
	char netID[12], hostID[12];
	for (int k = 0; k < 12; k++) {
		netID[k] = hostID[k] = '\0';
	}

	// for class A, only first octet is Network ID
	// and rest are Host ID
	if (ipClass == 'A') {
		int i = 0, j = 0;
		while (str[j] != '.') {
			netID[i++] = str[j++];
		}
		i = 0;
		j++;
		while (str[j] != '\0') {
			hostID[i++] = str[j++];
		}
		printf("Network ID is %s\n", netID);
		printf("Host ID is %s\n", hostID);
	}

	// for class B, first two octet are Network ID
	// and rest are Host ID
	else if (ipClass == 'B') {
		int i = 0, j = 0, dotCount = 0;

		// storing in netID[] up to 2nd dot
		// dotCount keeps track of number of dots or octets passed
		while (dotCount < 2) {
			netID[i++] = str[j++];
			if (str[j] == '.') {
				dotCount++;
			}
		}
		i = 0;
		j++;

		while (str[j] != '\0') {
			hostID[i++] = str[j++];
		}

		printf("Network ID is %s\n", netID);
		printf("Host ID is %s\n", hostID);
	}

	// for class C, first three octet are Network ID
	// and rest are Host ID
	else if (ipClass == 'C') {
		int i = 0, j = 0, dotCount = 0;

		// storing in netID[] up to 3rd dot
		// dotCount keeps track of number of
		// dots or octets passed
		while (dotCount < 3) {
			netID[i++] = str[j++];
			if (str[j] == '.') {
				dotCount++;
			}
		}

		i = 0;
		j++;

		while (str[j] != '\0') {
			hostID[i++] = str[j++];
		}

		printf("Network ID is %s\n", netID);
		printf("Host ID is %s\n", hostID);
	}else {
		// Class D and E are not divided in Network
		// and Host ID
		printf("In this Class, IP address is not"
		" divided into Network and Host ID\n");
	}
}

// Main function
int main() {
	char str[] = "192.226.12.11";
	char ipClass = findClassOfIP(str);
	printf("Class of the given IP address is %c\n", ipClass);
	separateID(str, ipClass);
	return 0;
}
