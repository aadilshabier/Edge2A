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
{"name":"Keanu Reeves"},{"name":"Carrie-Anne Moss"},{"name":"Laurence Fishburne"},{"name":"Hugo Weaving"},{"name":"Lilly Wachowski"},{"name":"Lana Wachowski"},{"name":"Joel Silver"},{"name":"Emil Eifrem"},{"name":"Charlize Theron"},{"name":"Al Pacino"},{"name":"Taylor Hackford"},{"name":"Tom Cruise"},{"name":"Jack Nicholson"},{"name":"Demi Moore"},{"name":"Kevin Bacon"},{"name":"Kiefer Sutherland"},{"name":"Noah Wyle"},{"name":"Cuba Gooding Jr."},{"name":"Kevin Pollak"},{"name":"J.T. Walsh"},{"name":"James Marshall"},{"name":"Christopher Guest"},{"name":"Rob Reiner"},{"name":"Aaron Sorkin"},{"name":"Kelly McGillis"},{"name":"Val Kilmer"},{"name":"Anthony Edwards"},{"name":"Tom Skerritt"},{"name":"Meg Ryan"},{"name":"Tony Scott"},{"name":"Jim Cash"},{"name":"Renee Zellweger"},{"name":"Kelly Preston"},{"name":"Jerry O'Connell"},{"name":"Jay Mohr"},{"name":"Bonnie Hunt"},{"name":"Regina King"},{"name":"Jonathan Lipnicki"},{"name":"Cameron Crowe"},{"name":"River Phoenix"},{"name":"Corey Feldman"},{"name":"Wil Wheaton"},{"name":"John Cusack"},{"name":"Marshall Bell"},{"name":"Helen Hunt"},{"name":"Greg Kinnear"},{"name":"James L. Brooks"},{"name":"Annabella Sciorra"},{"name":"Max von Sydow"},{"name":"Werner Herzog"},{"name":"Robin Williams"},{"name":"Vincent Ward"},{"name":"Ethan Hawke"},{"name":"Rick Yune"},{"name":"James Cromwell"},{"name":"Scott Hicks"},{"name":"Parker Posey"},{"name":"Dave Chappelle"},{"name":"Steve Zahn"},{"name":"Tom Hanks"},{"name":"Nora Ephron"},{"name":"Rita Wilson"},{"name":"Bill Pullman"},{"name":"Victor Garber"},{"name":"Rosie O'Donnell"},{"name":"John Patrick Stanley"},{"name":"Nathan Lane"},{"name":"Billy Crystal"},{"name":"Carrie Fisher"},{"name":"Bruno Kirby"},{"name":"Liv Tyler"},{"name":"Brooke Langton"},{"name":"Gene Hackman"},{"name":"Orlando Jones"},{"name":"Howard Deutch"},{"name":"Christian Bale"},{"name":"Zach Grenier"},{"name":"Mike Nichols"},{"name":"Richard Harris"},{"name":"Clint Eastwood"},{"name":"Takeshi Kitano"},{"name":"Dina Meyer"},{"name":"Ice-T"},{"name":"Robert Longo"},{"name":"Halle Berry"},{"name":"Jim Broadbent"},{"name":"Tom Tykwer"},{"name":"David Mitchell"},{"name":"Stefan Arndt"},{"name":"Ian McKellen"},{"name":"Audrey Tautou"},{"name":"Paul Bettany"},{"name":"Ron Howard"},{"name":"Natalie Portman"},{"name":"Stephen Rea"},{"name":"John Hurt"},{"name":"Ben Miles"},{"name":"Emile Hirsch"},{"name":"John Goodman"},{"name":"Susan Sarandon"},{"name":"Matthew Fox"},{"name":"Christina Ricci"},{"name":"Rain"},{"name":"Naomie Harris"},{"name":"Michael Clarke Duncan"},{"name":"David Morse"},{"name":"Sam Rockwell"},{"name":"Gary Sinise"},{"name":"Patricia Clarkson"},{"name":"Frank Darabont"},{"name":"Frank Langella"},{"name":"Michael Sheen"},{"name":"Oliver Platt"},{"name":"Danny DeVito"},{"name":"John C. Reilly"},{"name":"Ed Harris"},{"name":"Bill Paxton"},{"name":"Philip Seymour Hoffman"},{"name":"Jan de Bont"},{"name":"Robert Zemeckis"},{"name":"Milos Forman"},{"name":"Diane Keaton"},{"name":"Nancy Meyers"},{"name":"Chris Columbus"},{"name":"Julia Roberts"},{"name":"Madonna"},{"name":"Geena Davis"},{"name":"Lori Petty"},{"name":"Penny Marshall"},{"name":"Paul Blythe"},{"name":"Angela Scope"},{"name":"Jessica Thompson"},{"name":"James Thompson"},
];

const roles = ["Any", "Actor", "Director", "Producer", "Writer"];

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
      setFilters([...filters, { name: validPerson.name, role: selectedRole }]);
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
	  console.log("Filters: ", JSON.stringify(filters));
	  fetch('http://localhost:3001/movies', {
		  method: 'POST',
		  body: JSON.stringify(filters)
	  })
		  .then(response => response.json())
		  .then(data => {
			  setSearchResults(data);
			  console.log('Received from backend:', data);
		  })
		  .catch(error => {
			  console.error('Error:', error);
		  });
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
                {filter.name} ({filter.role})
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
                            {p.name}
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
