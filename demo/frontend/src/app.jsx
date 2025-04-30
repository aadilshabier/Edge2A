import React, { useState } from "react";
import {
  ChakraProvider,
  Box,
  Heading,
  Button,
  VStack,
  HStack,
  Text,
  Modal,
  ModalOverlay,
  ModalContent,
  ModalHeader,
  ModalCloseButton,
  ModalBody,
  ModalFooter,
  Select,
  Input,
  Tag,
  TagLabel,
  TagCloseButton,
  SimpleGrid,
} from "@chakra-ui/react";

const persons = [
  { name: "Tom Hanks", year: 1956 },
  { name: "Christopher Nolan", year: 1970 },
  { name: "Natalie Portman", year: 1981 },
];

const roles = ["Any", "Actor", "Director", "Producer", "Writer"];

const staticMovies = [
  { title: "Inception", year: 2010, tagline: "Your mind is the scene of the crime." },
  { title: "Forrest Gump", year: 1994, tagline: "Life is like a box of chocolates." },
];

function App() {
  const [filters, setFilters] = useState([]);
  const [showModal, setShowModal] = useState(false);
  const [selectedPerson, setSelectedPerson] = useState("");
  const [selectedRole, setSelectedRole] = useState("");
  const [searchResults, setSearchResults] = useState([]);
  const [dropdownOpen, setDropdownOpen] = useState(false);

  // Filter only valid matches
  const filteredPersons = persons.filter((p) =>
    p.name.toLowerCase().includes(selectedPerson.toLowerCase())
  );

  const addFilter = () => {
    const validPerson = persons.find((p) => p.name === selectedPerson);
    if (validPerson && selectedRole) {
      setFilters([...filters, { person: validPerson.name, role: selectedRole }]);
      setSelectedPerson("");
      setSelectedRole("");
      setShowModal(false);
      setDropdownOpen(false);
    }
  };

  const removeFilter = (index) => {
    setFilters(filters.filter((_, i) => i !== index));
  };

  const clearFilters = () => {
    setFilters([]);
    setSelectedPerson("");
    setSelectedRole("");
    setShowModal(false);
    setDropdownOpen(false);
    setSearchResults([]);
  };

  const handleSearch = () => {
    // Simulate API call
    setSearchResults(staticMovies);
  };

  return (
    <ChakraProvider>
      <Box p={6}>
        <Heading mb={6}>Graph Demo</Heading>
        <HStack mb={4} spacing={4}>
          <Button onClick={() => setShowModal(true)}>Add Filter</Button>
          <Button onClick={() => clearFilters()}>Clear Filters</Button>
          <Button colorScheme="teal" onClick={handleSearch}>
            Search
          </Button>
        </HStack>

        <HStack spacing={4} mb={6}>
          {filters.map((filter, index) => (
            <Tag size="lg" key={index} borderRadius="full" variant="solid" colorScheme="blue">
              <TagLabel>
                {filter.person} ({filter.role})
              </TagLabel>
              <TagCloseButton onClick={() => removeFilter(index)} />
            </Tag>
          ))}
        </HStack>

        <SimpleGrid columns={1} spacing={4}>
          {searchResults.map((movie, idx) => (
            <Box key={idx} p={4} borderWidth="1px" borderRadius="lg">
              <Text fontWeight="bold">{movie.title}</Text>
              <Text>{movie.year}</Text>
              <Text fontStyle="italic">{movie.tagline}</Text>
            </Box>
          ))}
        </SimpleGrid>

        <Modal isOpen={showModal} onClose={() => setShowModal(false)}>
          <ModalOverlay />
          <ModalContent>
            <ModalHeader>Add Filter</ModalHeader>
            <ModalCloseButton />
            <ModalBody>
              <VStack spacing={4} align="stretch">
                {/* Typable Person Select with controlled dropdown */}
                <Box position="relative">
                  <Text mb={1}>Select Person</Text>
                  <Input
                    placeholder="Type to search..."
                    value={selectedPerson}
                    onChange={(e) => {
                      setSelectedPerson(e.target.value);
                      setDropdownOpen(true);
                    }}
                    onFocus={() => setDropdownOpen(true)}
                  />
                  {dropdownOpen &&
                    filteredPersons.length > 0 &&
                    (
                      <Box
                        mt={1}
                        border="1px solid"
                        borderColor="gray.200"
                        borderRadius="md"
                        maxHeight="150px"
                        overflowY="auto"
                        bg="white"
                        position="absolute"
                        width="100%"
                        zIndex="popover"
                      >
                        {filteredPersons.map((p, i) => (
                          <Box
                            key={i}
                            px={3}
                            py={2}
                            _hover={{ bg: "gray.100", cursor: "pointer" }}
                            onClick={() => {
                              setSelectedPerson(p.name);
                              setDropdownOpen(false);
                            }}
                          >
                            {p.name} ({p.year})
                          </Box>
                        ))}
                      </Box>
                    )}
                </Box>

                {/* Role Dropdown */}
                <Box>
                  <Text mb={1}>Select Role</Text>
                  <Select
                    placeholder="Select role"
                    value={selectedRole}
                    onChange={(e) => setSelectedRole(e.target.value)}
                  >
                    {roles.map((role, i) => (
                      <option key={i} value={role}>
                        {role}
                      </option>
                    ))}
                  </Select>
                </Box>
              </VStack>
            </ModalBody>
            <ModalFooter>
              <Button colorScheme="blue" mr={3} onClick={addFilter}>
                Add
              </Button>
              <Button onClick={() => setShowModal(false)}>Cancel</Button>
            </ModalFooter>
          </ModalContent>
        </Modal>
      </Box>
    </ChakraProvider>
  );
}

export default App;
