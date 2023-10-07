#define CATCH_CONFIG_MAIN

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <unordered_set>
#include <random>
#include "../src/AVL.h"
#include "../src/Parser.h"

TEST_CASE("Test Cases 1: Testing Incorrect Commands", "[commands]") {

    AVLTree tree;

    SECTION("Unsuccessful Insert with Numbers in Name") {
        istringstream sim_cin("1\ninsert \"A11y\" 45679999\n");
        streambuf* cinbuf = cin.rdbuf();
        cin.rdbuf(sim_cin.rdbuf());

        ostringstream sim_cout;
        streambuf* coutbuf = cout.rdbuf(sim_cout.rdbuf());

        handleUserCommands(tree);

        cin.rdbuf(cinbuf);
        cout.rdbuf(coutbuf);

        string expectedOutput = "unsuccessful\n";
        REQUIRE(sim_cout.str() == expectedOutput);
    }

    SECTION("Unsuccessful Insert with Letters in UFID") {
        istringstream sim_cin("1\ninsert \"Daniel\" 456799bb\n");
        streambuf* cinbuf = cin.rdbuf();
        cin.rdbuf(sim_cin.rdbuf());

        ostringstream sim_cout;
        streambuf* coutbuf = cout.rdbuf(sim_cout.rdbuf());

        handleUserCommands(tree);

        cin.rdbuf(cinbuf);
        cout.rdbuf(coutbuf);

        string expectedOutput = "unsuccessful\n";
        REQUIRE(sim_cout.str() == expectedOutput);
    }

    SECTION("Unsuccessful remove with name instead of UF ID"){
        istringstream sim_cin("2\ninsert \"Daniel\" 45679999\nremove \"Daniel\"\n");
        streambuf* cinbuf = cin.rdbuf();
        cin.rdbuf(sim_cin.rdbuf());

        ostringstream sim_cout;
        streambuf* coutbuf = cout.rdbuf(sim_cout.rdbuf());

        handleUserCommands(tree);

        cin.rdbuf(cinbuf);
        cout.rdbuf(coutbuf);

        string expectedOutput = "successful\nunsuccessful\n";
        REQUIRE(sim_cout.str() == expectedOutput);
    }

    SECTION("Unsuccessful removeInorder"){
        istringstream sim_cin("3\ninsert \"Daniel\" 45679999\nremoveInorder 1\nremoveInorder \"Daniel\"\n");
        streambuf* cinbuf = cin.rdbuf();
        cin.rdbuf(sim_cin.rdbuf());

        ostringstream sim_cout;
        streambuf* coutbuf = cout.rdbuf(sim_cout.rdbuf());

        handleUserCommands(tree);

        cin.rdbuf(cinbuf);
        cout.rdbuf(coutbuf);

        string expectedOutput = "successful\nunsuccessful\nunsuccessful\n";
        REQUIRE(sim_cout.str() == expectedOutput);
    }

    SECTION("Unsuccessful search with numbers and letters mixed"){
        istringstream sim_cin("3\ninsert \"Daniel\" 45679999\nsearch \"Da4iel\"\n");
        streambuf* cinbuf = cin.rdbuf();
        cin.rdbuf(sim_cin.rdbuf());

        ostringstream sim_cout;
        streambuf* coutbuf = cout.rdbuf(sim_cout.rdbuf());

        handleUserCommands(tree);

        cin.rdbuf(cinbuf);
        cout.rdbuf(coutbuf);

        string expectedOutput = "successful\nunsuccessful\n";
        REQUIRE(sim_cout.str() == expectedOutput);
    }

    // Add more sections for other commands like remove, search etc.
}

TEST_CASE("Test Cases 2: Edge Cases", "[edge]"){
    AVLTree tree;

    SECTION("Unsuccessful removing a node that does not exist"){
        ostringstream buffer;
        streambuf* coutbuf = cout.rdbuf(buffer.rdbuf());

        tree.Insert("Daniel", "27355784");
        tree.Insert("Jacob", "5318008");
        tree.Insert("Deez", "8093853");
        tree.Remove("23232322");

        cout.rdbuf(coutbuf);

        string expectedOutput = "successful\nsuccessful\nsuccessful\nunsuccessful\n";
        REQUIRE(buffer.str() == expectedOutput);
    }

    SECTION("Unsuccessful removing Inorder a node that does not exist"){
        ostringstream buffer;
        streambuf* coutbuf = cout.rdbuf(buffer.rdbuf());

        tree.Insert("Daniel", "27355784");
        tree.Insert("Jacob", "5318008");
        tree.RemoveInOrder(3);

        cout.rdbuf(coutbuf);

        string expectedOutput = "successful\nsuccessful\nunsuccessful\n";
        REQUIRE(buffer.str() == expectedOutput);
    }

    SECTION("Unsuccessful searching for a node that doesn't exist"){
        ostringstream buffer;
        streambuf* coutbuf = cout.rdbuf(buffer.rdbuf());

        tree.Insert("Daniel", "27355784");
        tree.Insert("Jacob", "5318008");
        tree.SearchID("23232322");
        tree.SearchName("Nick");

        cout.rdbuf(coutbuf);

        string expectedOutput = "successful\nsuccessful\nunsuccessful\nunsuccessful\n";
        REQUIRE(buffer.str() == expectedOutput);
    }

    SECTION("Inserting multiple ID's for a name"){
        ostringstream buffer;
        streambuf* coutbuf = cout.rdbuf(buffer.rdbuf());

        tree.Insert("Daniel", "27355784");
        tree.Insert("Jacob", "5318008");
        tree.Insert("Daniel", "99999999");
        tree.Insert("Jacob", "23232322");

        cout.rdbuf(coutbuf);

        string expectedOutput = "successful\nsuccessful\nsuccessful\nsuccessful\n";
        REQUIRE(buffer.str() == expectedOutput);
    }
}

TEST_CASE("Test Cases 3: AVL Rotations", "[rotation]") {
    AVLTree tree;

    SECTION("Left Rotation (Left-Left Imbalance)") {
        ostringstream buffer;
        streambuf* coutbuf = cout.rdbuf(buffer.rdbuf());

        tree.Insert("Daniel", "32345678");
        tree.Insert("Jacob", "22345678");
        tree.Insert("Kameon", "12345678");

        cout.rdbuf(coutbuf);

        REQUIRE(tree.getRoot()->ufid == "22345678");
    }

    SECTION("Right Rotation (Right-Right Imbalance)") {
        ostringstream buffer;
        streambuf* coutbuf = cout.rdbuf(buffer.rdbuf());

        tree.Insert("Kameon", "12345678");
        tree.Insert("Daniel", "22345678");
        tree.Insert("Jacob", "32345678");

        cout.rdbuf(coutbuf);

        REQUIRE(tree.getRoot()->ufid == "22345678");
    }

    SECTION("Left-Right Rotation (Left-Right Imbalance)") {
        ostringstream buffer;
        streambuf* coutbuf = cout.rdbuf(buffer.rdbuf());

        tree.Insert("Jacob", "32345678");
        tree.Insert("Kameon", "12345678");
        tree.Insert("Daniel", "22345678");

        cout.rdbuf(coutbuf);

        REQUIRE(tree.getRoot()->ufid == "22345678");
    }

    SECTION("Right-Left Rotation (Right-Left Imbalance)") {
        ostringstream buffer;
        streambuf* coutbuf = cout.rdbuf(buffer.rdbuf());

        tree.Insert("Alice", "12345678");
        tree.Insert("Jacob", "32345678");
        tree.Insert("Daniel", "22345678");

        cout.rdbuf(coutbuf);

        REQUIRE(tree.getRoot()->ufid == "22345678");
    }
}

TEST_CASE("Test Cases 4: AVL Deletions", "[deletion]") {
    AVLTree tree;

    SECTION("Delete node with no children") {
        ostringstream buffer;
        streambuf* coutbuf = cout.rdbuf(buffer.rdbuf());

        tree.Insert("Daniel", "27355784");
        tree.Remove("27355784");

        cout.rdbuf(coutbuf);

        string expectedOutput = "successful\nsuccessful\n";
        REQUIRE(buffer.str() == expectedOutput);
        REQUIRE(tree.getRoot() == nullptr);
    }

    SECTION("Delete node with one right child") {
        ostringstream buffer;
        streambuf* coutbuf = cout.rdbuf(buffer.rdbuf());

        tree.Insert("Daniel", "27355784");
        tree.Insert("Jacob", "5318008");
        tree.Remove("27355784");

        cout.rdbuf(coutbuf);

        string expectedOutput = "successful\nsuccessful\nsuccessful\n";
        REQUIRE(buffer.str() == expectedOutput);
        REQUIRE(tree.getRoot()->ufid == "5318008");
    }

    SECTION("Delete node with one left child") {
        ostringstream buffer;
        streambuf* coutbuf = cout.rdbuf(buffer.rdbuf());

        tree.Insert("Daniel", "27355784");
        tree.Insert("Jacob", "12345678");
        tree.Remove("27355784");

        cout.rdbuf(coutbuf);

        string expectedOutput = "successful\nsuccessful\nsuccessful\n";
        REQUIRE(buffer.str() == expectedOutput);
        REQUIRE(tree.getRoot()->ufid == "12345678");
    }

    SECTION("Delete node with two children") {
        ostringstream buffer;
        streambuf* coutbuf = cout.rdbuf(buffer.rdbuf());

        tree.Insert("Daniel", "27355784");
        tree.Insert("Alice", "12345678");
        tree.Insert("Eve", "22345678");
        tree.Insert("Jacob", "32345678");
        tree.Remove("27355784");

        cout.rdbuf(coutbuf);

        string expectedOutput = "successful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\n";
        REQUIRE(buffer.str() == expectedOutput);
        REQUIRE(tree.getRoot()->ufid == "22345678");
    }
}

TEST_CASE("Test Cases 5: BST Insert Large", "[flag]") {
    AVLTree tree;

    // Store the inserted UFIDs to later remove them randomly
    vector<string> insertedUFIDs;

    for (int i = 0; i < 100; i++) {
        string randomName = generateRandomString(5);
        string randomUFID = to_string(rand() % 90000000 + 10000000);

        // Store the UFID
        insertedUFIDs.push_back(randomUFID);

        ostringstream buffer;
        streambuf *coutbuf = cout.rdbuf(buffer.rdbuf());

        tree.Insert(randomName, randomUFID);
        cout.rdbuf(coutbuf);

        REQUIRE(buffer.str() == "successful\n");
    }

    int nodeCount = tree.countNodes(tree.getRoot());
    REQUIRE(nodeCount == 100);

    // Shuffle the inserted UFIDs to remove them in random order
    random_shuffle(insertedUFIDs.begin(), insertedUFIDs.end());

    // Remove the first 10 UFIDs from the shuffled list
    for (int i = 0; i < 10; i++) {
        ostringstream buffer;
        streambuf *coutbuf = cout.rdbuf(buffer.rdbuf());

        tree.Remove(insertedUFIDs[i]);
        cout.rdbuf(coutbuf);

        REQUIRE(buffer.str() == "successful\n");
    }

    nodeCount = tree.countNodes(tree.getRoot());

    REQUIRE(nodeCount == 90);

    SECTION("Verifying inOrder after inserting 100 nodes and removing 10") {
        vector<string> inOrderResult = tree.inOrderUFIDs();

        REQUIRE(inOrderResult.size() == 90);

        for (size_t i = 0; i < inOrderResult.size() - 1; ++i) {
            REQUIRE(stoi(inOrderResult[i]) < stoi(inOrderResult[i + 1]));
        }
    }
}